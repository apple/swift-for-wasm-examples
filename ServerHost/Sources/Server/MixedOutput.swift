import Hummingbird
import WasmKit

struct MixedOutput: ResponseGenerator {
    init(modules: [IndexPage.Module]) throws {
        self.modules = try modules.map { try parseWasm(filePath: $0.path) }
    }
    
    var modules: [Module]

    func response(from request: Request, context: some RequestContext) throws -> Response {
        var body = ByteBuffer()
        let runtime = Runtime()

        // Instantiate each Wasm module
        for module in modules {
            let moduleInstance = try runtime.instantiate(module: module)

            // Call entrypoint module function
            let results = try runtime.invoke(moduleInstance, function: "main")
            for case .f32(let bitPattern) in results {
                body.writeInteger(bitPattern)
            }
        }

        return Response(status: .ok, body: .init(byteBuffer: body))
    }
}
