/// Number of samples generated per second.
let sampleRate = 44100

/// Stateless sawtooth-shaped waveform function.
/// - Parameters:
///   - time: Number of seconds passed since the current oscillation started.
///   - frequency: Frequency of oscillation, in hertz.
/// - Returns: An audio sample in the normalized range of -1.0...1.0
func saw(time: Float, frequency: Float) -> Float {
    let phase = time * frequency

    return 2 * (phase - (0.5 + phase).rounded(.down))
}

/// Stateful sawtooth-shaped signal.
struct Saw: Signal {
    /// Frequency of oscillation, in hertz.
    var frequency: Float = 440.0

    /// The "volume" of the signal, i.e. the absolute boundary of the range in which this signal oscillates. Default
    /// amplitude of 1.0 means that samples returned from ``Saw/next()`` will always stay in `-1.0...1.0` range.
    var amplitude: Float = 1.0

    /// Number of seconds passed since the current oscillation started. To avoid overflowing, this value is reset
    /// to 0.0 after every oscillation.
    var currentTime: Float = 0.0

    mutating func next() -> Float {
        let result = saw(time: currentTime, frequency: frequency)

        currentTime += 1.0 / Float(sampleRate)
        if currentTime > 1.0 / frequency {
            currentTime = 0
        }

        return result * amplitude
    }
}
