/// An abstract digital signal that produces an infinite amount of samples.
protocol Signal {
    /// Updates current state of the signal and produces the next sample.
    /// - Returns: The latest sample in this signal.
    mutating func next() -> Float
}
