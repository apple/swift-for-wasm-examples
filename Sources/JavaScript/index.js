import { Encoder } from './encoder.js';

const canvasElement = document.getElementById('tutorial');
const canvasContext = canvasElement.getContext('2d');
canvasContext.strokeStyle = 'white';

const decoder = new TextDecoder();
const loggerElement = document.getElementById('wasm-logger');

function wasmMemoryAsString(address, byteCount) {
  return decoder.decode(instance.exports.memory.buffer.slice(address, address + byteCount));
}

function wasmMemoryAsFloat32Array(address, byteCount) {
  return new Float32Array(instance.exports.memory.buffer.slice(address, address + byteCount));
}

function generate() {
  const blob = wavEncoder.finish();
  const audioURL = URL.createObjectURL(blob);
  document.getElementById('audio').setAttribute('src', audioURL);
}

const wavEncoder = new Encoder(44100, 1);

const importsObject = {
  audio: {
    encode: (address, byteCount) => {
      wavEncoder.encode([wasmMemoryAsFloat32Array(address, byteCount)])
      generate();
    },
  },
  canvas: {
    beginPath: () => canvasContext.beginPath(),
    stroke: () => canvasContext.stroke(),
    moveTo: (x, y) => canvasContext.moveTo(x, y),
    lineTo: (x, y) => canvasContext.lineTo(x, y),
  }, 
  console: {
    log: (address, byteCount) => {
      loggerElement.innerHTML = wasmMemoryAsString(address, byteCount);
    },
    logInt: (int) => console.log(int),
    logFloat: (int) => console.log(int),
  }
};

const { instance } = await WebAssembly.instantiateStreaming(
  fetch('.build/wasm32-unknown-none-wasm/release/swift-audio.wasm'),
  {
    ...importsObject,
  }
);

instance.exports.main();
