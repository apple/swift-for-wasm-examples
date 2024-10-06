import Hummingbird
import WasmKit

struct MixedOutput: ResponseGenerator {
    init(modules: [IndexPage.Module]) throws {
        self.modules = try modules.map {
            try parseWasm(filePath: $0.absolutePath)
        }
    }
    
    var modules: [Module]

    func response(from request: Request, context: some RequestContext) throws -> Response {
        var samples = [Float32]()
        var memoryIndex = 0

        let runtime = Runtime(
            hostModules: ["audio": .init(
                functions: [
                    "encode": HostFunction(type: .init(
                        parameters: [.i32, .i32, .i32]
                    )) { caller, args in
                        let start = args[1].i32
                        let byteCount = args[2].i32

                        // Read audio buffer from Wasm linear memory.
                        caller.runtime.store.memory(
                            at: memoryIndex
                        ).data[Int(start)..<Int(start + byteCount)].withUnsafeBytes {
                            // Rebind memory bytes to `Float32`.
                            $0.withMemoryRebound(to: Float32.self) {
                                // Enumerate each floating point sample
                                for (i, sample) in $0.enumerated() {
                                    // Extend `samples` buffer if needed.
                                    if samples.count < $0.count {
                                        // 0.0 (no signal) is the default sample.
                                        samples.append(0.0)
                                    }

                                    // Mix current sample with an existing value.
                                    samples[i] += sample
                                }

                                assert(samples.count == $0.count)
                            }
                        }

                        return []
                    }
                ]
            )]
        )

        // Instantiate each Wasm module
        for module in modules {
            let moduleInstance = try runtime.instantiate(module: module)

            // Call entrypoint module function
            _ = try runtime.invoke(moduleInstance, function: "main", with: [.i32(0)])
            memoryIndex += 1
        }

        var body = ByteBuffer()
        samples.withUnsafeBytes {
            _ = body.writeBytes($0)
        }

        return Response(status: .ok, body: .init(byteBuffer: body))
    }
}
