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

import { Encoder } from './encoder.js';

const decoder = new TextDecoder();
const loggerElement = document.getElementById('wasm-logger');
const moduleInstances = [];

function wasmMemoryAsString(i, address, byteCount) {
  return decoder.decode(moduleInstances[i].exports.memory.buffer.slice(address, address + byteCount));
}

function wasmMemoryAsFloat32Array(i, address, byteCount) {
  return new Float32Array(moduleInstances[i].exports.memory.buffer.slice(address, address + byteCount));
}

function generate(i) {
  const blob = wavEncoder.finish();
  const audioURL = URL.createObjectURL(blob);
  document.getElementsByClassName('audio')[i].setAttribute('src', audioURL);
}

const wavEncoder = new Encoder(44100, 1);
const contexts = [];

const importsObject = {
  audio: {
    encode: (i, address, byteCount) => {
      wavEncoder.encode([wasmMemoryAsFloat32Array(i, address, byteCount)])
      generate(i);
    },
  },
  canvas: {
    beginPath: (i) => contexts[i].beginPath(),
    stroke: (i) => contexts[i].stroke(),
    moveTo: (i, x, y) => contexts[i].moveTo(x, y),
    lineTo: (i, x, y) => contexts[i].lineTo(x, y),
  },
  console: {
    log: (i, address, byteCount) => {
      loggerElement.innerHTML = wasmMemoryAsString(i, address, byteCount);
    },
    logInt: (x) => console.log(x),
    logFloat: (x) => console.log(x),
  }
};

const pluginElements = document.getElementsByClassName("plugin");

for (let i = 0; i < pluginElements.length; ++i) {
  const element = pluginElements[i];
  const canvasElement = element.getElementsByClassName("plotter")[i];
  const canvasContext = canvasElement.getContext('2d');
  canvasContext.strokeStyle = 'white';

  contexts.push(canvasContext);

  const { instance } = await WebAssembly.instantiateStreaming(
    fetch(element.dataset.modulePath),
    { ...importsObject }
  );

  moduleInstances.push(instance);

  instance.exports.main(i);
}
