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

struct Square: Signal {
    var frequency: Float {
        didSet {
            self.saw.frequency = self.frequency
        }
    }
    var amplitude: Float
    var pulseWidth: Float

    private var saw: Saw

    init(
        frequency: Float = 440.0,
        amplitude: Float = 1.0,
        pulseWidth: Float = 0.5
    ) {
        self.frequency = frequency
        self.amplitude = amplitude
        self.pulseWidth = pulseWidth
        self.saw = Saw(frequency: frequency, amplitude: amplitude)
    }

    mutating func next() -> Float {
        if abs(self.saw.next()) > pulseWidth {
            amplitude
        } else {
            -amplitude
        }
    }
}