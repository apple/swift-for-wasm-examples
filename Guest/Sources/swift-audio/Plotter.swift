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

struct Plotter<CanvasType: Canvas> {
    let height: Int
    let width: Int
    let centerY: Int
    let scaleFactor: Float

    init(width: Int, height: Int, margin: Int) {
        self.width = width
        self.height = height
        self.centerY = (height + margin) / 2
        self.scaleFactor = Float(height) / 4.0
    }

    func plot(_ audioBuffer: borrowing AudioBuffer) {
        let samplesPerPixel = audioBuffer.storage.count / self.width

        var sampleCounter = 0
        var averageCounter = 0
        var average: Float = 0

        CanvasType.beginPath()
        CanvasType.moveTo(x: 0, y: self.centerY)
        for sample in audioBuffer.storage {
            average += sample

            if sampleCounter < samplesPerPixel {
                sampleCounter += 1
                average += sample
            } else {
                CanvasType.lineTo(
                    x: averageCounter,
                    y: self.centerY + Int(average * self.scaleFactor / Float(samplesPerPixel))
                )
                averageCounter += 1
                average = 0
                sampleCounter = 0
            }
        }

        if average != 0 {
            CanvasType.lineTo(
                x: averageCounter,
                y: self.centerY + Int(average * self.scaleFactor / Float(sampleCounter))
            )
        }

        CanvasType.stroke()
    }
}
