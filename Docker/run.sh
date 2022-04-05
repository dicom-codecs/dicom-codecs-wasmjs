docker run -it --rm \
  -v $HOME/src/github/dicom-codecs/dicom-codecs-wasmjs:/dicom-codecs-wasmjs -w /dicom-codecs-wasmjs \
  emscripten/emsdk bash