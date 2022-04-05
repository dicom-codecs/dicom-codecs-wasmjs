#!/bin/sh

RED='\033[0;31m'
NC='\033[0m' # No Color

rm -rf build
mkdir -p build
rm -rf dist/*
#(cd build && emcmake cmake -DCMAKE_BUILD_TYPE=Debug ..)
(cd build && emcmake cmake ..)
if [ $retVal -ne 0 ]; then
    echo "${RED}CMAKE FAILED${NC}"
    exit 1
fi

(cd build && emmake make VERBOSE=1 -j ${nprocs})
retVal=$?
if [ $retVal -ne 0 ]; then
    echo "${RED}MAKE FAILED${NC}"
    exit 1
fi
mkdir -p ./dist
cp ./build/src/dicomcodecswasm.js ./dist
cp ./build/src/dicomcodecswasm.wasm ./dist
#(cd test; node index.js)