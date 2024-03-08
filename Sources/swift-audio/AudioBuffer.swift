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

struct AudioBuffer: ~Copyable {
    let storage: UnsafeMutableBufferPointer<Float>

    init(capacity: Int) {
        self.storage = .allocate(capacity: capacity)
    }

    func fill(source: inout some Signal) {
        for i in self.storage.indices {
            let sample = source.next()
            self.storage[i] = sample
        }
    }

    deinit {
        self.storage.deallocate()
    }
}
