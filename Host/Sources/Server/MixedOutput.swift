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
        for module in modules {
            let moduleInstance = try runtime.instantiate(module: module)
            for value in try runtime.invoke(moduleInstance, function: "main") {
                switch value {
                case .f32(let bitPattern): body.writeInteger(bitPattern)
                default: continue
                }
            }
        }

        return Response(status: .ok, body: .init(byteBuffer: body))
    }
}
