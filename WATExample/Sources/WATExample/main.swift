import Foundation
import WasmKit
import WAT

// Compute WAT file path.
let watURL = URL(fileURLWithPath: #filePath)
    .deletingLastPathComponent()
    .deletingLastPathComponent()
    .deletingLastPathComponent()
    .appendingPathComponent("factorial.wat")

// Parse from WAT to binary Wasm module.
let binaryModule = try wat2wasm(String(decoding: Data(contentsOf: watURL), as: UTF8.self))

// Parse as WasmKit IR.
let parsedModule = try parseWasm(bytes: binaryModule)

// Initialize WasmKit runtime
let runtime = Runtime(
    hostModules: [
        "host": .init(
            functions: [
                // Pass host printer function as a closure
                "print": HostFunction(type: .init(parameters: [.i32, .i32])) { instance, args in
                    guard let start = args.first?.i32,
                          let offset = args.last?.i32
                    else { return [] }

                    // Decode linear memory
                    let string = String(
                        decoding: instance.store
                            .memory(at: 0)
                            .data[Int(start) ..< Int(start + offset)],
                        as: UTF8.self
                    )

                    // Print the result
                    print("Guest module printed: \(string)")
                    return []
                },
            ]
        ),
    ]
)

// Instantiate the module
let moduleInstance = try runtime.instantiate(module: parsedModule)

// Call `main` function
let result = try runtime.invoke(moduleInstance, function: "main")
print("Returned value: \(result)")
