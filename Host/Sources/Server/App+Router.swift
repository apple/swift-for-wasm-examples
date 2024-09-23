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

enum UploadError: Error {
    case invalidFileName
}

/// Build router
func buildRouter() -> Router<AppRequestContext> {
    Router(context: AppRequestContext.self)
        // Add middleware
        .addMiddleware {
            // logging middleware
            LogRequestsMiddleware(.info)
        }

        .get("/") { _, _ in
            Response(
                status: .temporaryRedirect,
                headers: [.location: "/public/index.html"]
            )
        }

        .get("/public/index.html") { _, _ in
            IndexPage(modules: [
                .init(name: "Mix", path: ".build/wasm32-unknown-none-wasm/release/swift-audio.wasm")
            ])
        }

        .get("/public/**") { req, ctx in
            // return catchAll captured string
            let path = ctx.parameters.getCatchAll().joined(separator: "/")

            return try await serveFile(path: storagePath.appending(path))
        }

        .post("/wasm-module/:name") { req, ctx in
            guard let fileName = ctx.parameters.get("name")
            else { throw UploadError.invalidFileName }

            try await FileSystem.shared.withFileHandle(
                forWritingAt: storagePath.appending(fileName),
                options: .newFile(replaceExisting: true)
            ) {
                var offset: Int64 = 0
                for try await buffer in req.body {
                    let count = buffer.readableBytes
                    try await $0.write(contentsOf: buffer, toAbsoluteOffset: offset)
                    offset += Int64(count)
                }
            }

            return HTTPResponse.Status.ok
        }
}
