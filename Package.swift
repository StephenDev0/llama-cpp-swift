// swift-tools-version: 5.9
import PackageDescription

let package = Package(
    name: "LLamaSwift",
    platforms: [
        .macOS(.v12),
        .iOS(.v14),
        .watchOS(.v4),
        .tvOS(.v14),
        .visionOS(.v1)
    ],
    products: [
        .library(
            name: "LLamaSwift",
            targets: ["LLamaSwift"]),
    ],
    dependencies: [
        // Using local stub dependencies to allow offline builds in the Codex
        // environment. Replace these with real package URLs in production.
    ],
    targets: [
        .target(
            name: "llama",
            path: "Sources/llama",
            publicHeadersPath: "include"
        ),
        .target(
            name: "Logging",
            path: "Sources/Logging"
        ),
        .target(
            name: "LLamaSwift",
            dependencies: [
                "llama",
                "Logging",
            ]
        ),
        .testTarget(
            name: "llama-cpp-swiftTests",
            dependencies: ["LLamaSwift"]
        ),
    ]
)
