import Hummingbird
import NIOFileSystem
@preconcurrency import SystemPackage

let storagePath = FilePath(#filePath)
    .removingLastComponent()
    .removingLastComponent()
    .removingLastComponent()
    .appending("Public")

private let contentTypes = [
    "html": "text/html",
    "css": "text/css",
    "js": "text/javascript",
    "wasm": "application/wasm",
    "txt": "text/plain",
    "png": "image/png",
    "jpg": "image/jpeg",
]

private func serveFile(path: FilePath) async throws -> Response {
    var headers = HTTPFields(dictionaryLiteral:
        (.contentType, contentTypes[path.extension ?? ""] ?? "application/octet-stream")
    )
    if let info = try await FileSystem.shared.info(forFileAt: path) {
        headers[.contentLength] = String(info.size)
    }

    return Response(
        status: .ok,
        headers: headers,
        body: ResponseBody { writer in
        try await FileSystem.shared.withFileHandle(forReadingAt: path) {
            for try await chunk in $0.readChunks() {
                try await writer.write(chunk)
            }
        }

        try await writer.finish(nil)
    })
}

/// Build router
func buildRouter() -> Router<AppRequestContext> {
    let router = Router(context: AppRequestContext.self)
    // Add middleware
    router.addMiddleware {
        // logging middleware
        LogRequestsMiddleware(.info)
    }

    router.get("/") { _, _ in
        Response(
            status: .temporaryRedirect,
            headers: [.location: "/public/index.html"]
        )
    }

    router.get("/public/**") { request, context in
        // return catchAll captured string
        let path = context.parameters.getCatchAll().joined(separator: "/")

        return try await serveFile(path: storagePath.appending(path))
    }

    router.post("/wasm-module/:name") { req, ctx -> HTTPResponse.Status in
        try await FileSystem.shared.withFileHandle(
            forWritingAt: storagePath.appending(ctx.parameters.get("name")!),
            options: .newFile(replaceExisting: true)
        ) {
            var offset: Int64 = 0
            for try await buffer in req.body {
                let count = buffer.readableBytes
                try await $0.write(contentsOf: buffer, toAbsoluteOffset: offset)
                offset += Int64(count)
            }
        }

        return .ok
    }

    return router
}
