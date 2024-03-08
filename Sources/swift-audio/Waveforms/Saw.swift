//===----------------------------------------------------------------------===//
//
// This source file is part of the Swift open source project
//
// Copyright (c) 2024 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

let sampleRate = 44_100

func saw(time: Float, frequency: Float) -> Float {
    let phase = time * frequency

    return 2 * (phase - (0.5 + phase).rounded(.down))
}

struct Saw: Signal {
    var frequency: Float = 440.0
    var amplitude: Float = 1.0
    var currentTime: Float = 0.0

    mutating func next() -> Float {
        let result = saw(time: currentTime, frequency: frequency)

        self.currentTime += 1.0 / Float(sampleRate)
        if self.currentTime > 1.0 / self.frequency {
            self.currentTime = 0
        }

        return result * self.amplitude
    }
}
