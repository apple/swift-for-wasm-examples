// swift-tools-version: 6.0
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "WasmHost",
    platforms: [.macOS(.v10_15)],
    dependencies: [
        .package(url: "https://github.com/swiftwasm/WasmKit.git", from: "0.0.8"),
        .package(url: "https://github.com/vapor/vapor.git", from: "4.99.3"),
    ],
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.
        .executableTarget(
            name: "WATExample",
            dependencies: [
                .product(name: "WAT", package: "WasmKit"),
                .product(name: "WasmKit", package: "WasmKit"),
            ]
        ),
        .executableTarget(
            name: "App",
            dependencies: [
                .product(name: "Vapor", package: "vapor"),
            ]
        ),
        .testTarget(
            name: "AppTests",
            dependencies: [
                .target(name: "App"),
                .product(name: "XCTVapor", package: "vapor"),
            ]
        )
    ]
)
