import Hummingbird
import SystemPackage

private func serveHTML(_ string: String) -> Response {
    .init(
        status: .ok,
        headers: .init(dictionaryLiteral: (.contentType, "text/html"), (.contentLength, "\(string.utf8.count)")),
        body: .init(byteBuffer: .init(string: string))
    )
}

struct IndexPage: ResponseGenerator {
    struct Module {
        let name: String
        let path: FilePath
    }

    let modules: [Module]

    func response(from request: Request, context: some RequestContext) throws -> Response {
        serveHTML(
            """
            <html>
              <head>
                <meta charset="utf-8">
                <title>Swift Audio Workstation</title>
              </head>
              <body>
                <script type="module" src="/public/Sources/JavaScript/index.js">
                </script>
                <style>
                body {
                  background-color: black;
                  padding: 1rem;
                }
                #wasm-logger {
                  font-family: sans-serif;
                  color: white;
                }
                </style>
              </body>
              \(modules.map { module in
              """
              <h1 id="wasm-logger">\(module.name)</h1>
              <div
                class="moduleNode"
                data-module-path="\(module.path)"
                style="display: flex; flex-direction: column; align-items: flex-start; gap: 1rem;"
              >
                <canvas class="plotter" width="1000" height="210"></canvas>
                <audio class="audio" type="audio.wav" controls></audio>
              </div>
              """
              }.joined(separator: "\n"))
            </html>
            """
        )
    }
}
