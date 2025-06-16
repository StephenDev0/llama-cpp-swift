public struct Logger {
    public let label: String
    public init(label: String) { self.label = label }
    public func debug(_ message: @autoclosure () -> String) {}
    public func error(_ message: @autoclosure () -> String) {}
}

public enum Logging {
    public static func bootstrap(_ factory: () -> Logger) {}
}
