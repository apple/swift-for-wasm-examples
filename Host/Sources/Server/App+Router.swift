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
func buildRouter() async throws -> Router<AppRequestContext> {
    let wasmModules = try await discoverModules(
        directory: storagePath.appending(".build/wasm32-unknown-none-wasm/release"),
        root: storagePath
    )

    return Router(context: AppRequestContext.self)
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
            IndexPage(modules: wasmModules)
        }

        .get("/mix") { _, _ in
            try MixedOutput(modules: wasmModules)
        }

        .get("/public/**") { req, ctx in
            // return catchAll captured string
            let path = ctx.parameters.getCatchAll().joined(separator: "/")

            return try await serveFile(path: storagePath.appending(path))
        }
}
