# dicom-codecs-wasmjs
WASM build of dicom-codecs for JavaScript (browser and Node)

## Building

This project uses git submodules to pull in external codec linbraries, initialize them first:

> git submodule update --init --recursive

This project uses a docker container to build, build the container:

> (cd Docker; ./build.sh)

Create a shell in the docker container

> Docker/docker.sh

Once inside the docker container, build it:

> ./build.sh

## Development

To update external dependencies to latest versions:

> git submodule update --remote --merge
