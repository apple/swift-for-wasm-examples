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

import VultDSP

struct Triangle: Signal {
    var pitch: Pitch
    var amplitude: Float = 1.0

    var state = Triangle__ctx_type_0()

    mutating func next() -> Float {
        Triangle_process(&self.state, self.pitch.rawValue / 10.0, 0, 0) * self.amplitude
    }
}
