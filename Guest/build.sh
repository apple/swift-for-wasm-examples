#!/bin/sh

set -eux

bin_path=$(swift build --triple wasm32-unknown-none-wasm -c release --show-bin-path)

for n in Bass HiHat Kick Mix; do
  swift build --triple wasm32-unknown-none-wasm -c release --product $n

  cp "${bin_path}/${n}.wasm" ~/Desktop
done


