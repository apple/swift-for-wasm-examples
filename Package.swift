// swift-tools-version: 6.0
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "swift-for-wasm-example",
    platforms: [.macOS(.v14)],
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.
        .executableTarget(
            name: "swift-audio",
            dependencies: ["dlmalloc", "VultDSP"],
            cSettings: [.unsafeFlags(["-fdeclspec"])],
            swiftSettings: [
                .enableExperimentalFeature("Embedded"), 
                .interoperabilityMode(.Cxx),
                .unsafeFlags(["-wmo", "-disable-cmo", "-Xfrontend", "-gnone"])
            ],
            linkerSettings: [
                .unsafeFlags([
                    "-use-ld=/opt/homebrew/opt/llvm/bin/wasm-ld",
                    "-Xclang-linker", "-nostdlib",
                    "-Xlinker", "--no-entry"
                ])
            ]
        ),
        .target(name: "VultDSP"),
        .target(
            name: "dlmalloc",
            cSettings: [
                .define("LACKS_TIME_H"),
                .define("LACKS_SYS_TYPES_H"),
                .define("LACKS_STDLIB_H"),
                .define("LACKS_STRING_H"),
                .define("LACKS_SYS_MMAN_H"),
                .define("LACKS_FCNTL_H"),
                .define("NO_MALLOC_STATS", to: "1"),
                .define("__wasilibc_unmodified_upstream"),
            ]
        ),
    ]
)
