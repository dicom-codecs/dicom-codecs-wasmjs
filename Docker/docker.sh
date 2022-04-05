docker run -it --rm \
  --user $(id -u):$(id -g) \
  -v $HOME/src/github/dicom-codecs/dicom-codecs-wasmjs:/dicom-codecs-wasmjs -w /dicom-codecs-wasmjs \
  dicomcodecjsbuild bash