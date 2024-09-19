import Foundation
import WasmKit
import WAT

let watURL = URL(fileURLWithPath: #filePath)
    .deletingLastPathComponent()
    .deletingLastPathComponent()
    .deletingLastPathComponent()
    .appendingPathComponent("demo.wat")

let binaryModule = try wat2wasm(String(decoding: Data(contentsOf: watURL), as: UTF8.self))

let parsedModule = try parseWasm(bytes: binaryModule)

let runtime = Runtime(
    hostModules: [
        "host": .init(
            functions: [
                "print": HostFunction(type: .init(parameters: [.i32, .i32])) { instance, args in
                    guard let start = args.first?.i32,
                          let offset = args.last?.i32
                    else { return [] }

                    let string = String(
                        decoding: instance.store
                            .memory(at: 0)
                            .data[Int(start) ..< Int(start + offset)],
                        as: UTF8.self
                    )

                    print("Guest module printed: \(string)")
                    return []
                },
            ]
        ),
    ]
)
let moduleInstance = try runtime.instantiate(module: parsedModule)
let result = try runtime.invoke(moduleInstance, function: "main")
print("Returned value: \(result)")
