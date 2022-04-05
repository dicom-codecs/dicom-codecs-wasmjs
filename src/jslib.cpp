// Copyright (c) Chris Hafey.
// SPDX-License-Identifier: MIT

#include <dicomcodecs/codec.hpp>
#include <dicomcodecs/image.hpp>

#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;

static std::vector<uint8_t> encoded_;
static dicomcodecs::image image_;

static void zinit()
{
    init();
}

static std::string getVersion()
{
  std::string version = "1.0";
  return version;
}

static void zencode(std::string codec) {
    encode(image_, encoded_, codec);
}

static void zdecode(std::string codec) {
    decode(encoded_, image_, codec);
}

static emscripten::val getEncodedBuffer(size_t encodedSize) {
    encoded_.resize(encodedSize);
    return emscripten::val(emscripten::typed_memory_view(encoded_.size(), encoded_.data()));
}

static emscripten::val getDecodedBuffer() {
    return emscripten::val(emscripten::typed_memory_view(image_.rawBytes.size(), image_.rawBytes.data()));
}

static dicomcodecs::image& getImage() {
    return image_;
}

EMSCRIPTEN_BINDINGS(dicomcodecswasm)
{
  function("init", &zinit);
  function("getVersion", &getVersion);
  function("getImage", &getImage);
  function("getEncodedBuffer", &getEncodedBuffer);
  function("getDecodedBuffer", &getDecodedBuffer);
  function("encode", &zencode);
  function("decode", &zdecode);
}

using namespace dicomcodecs;

EMSCRIPTEN_BINDINGS(image)
{
  value_object<image>("Image")
      .field("width", &dicomcodecs::image::width)
      .field("height", &dicomcodecs::image::height)
      .field("bitsPerSample", &dicomcodecs::image::bitsPerSample)
      .field("componentCount", &dicomcodecs::image::componentCount)
      .field("isSigned", &dicomcodecs::image::isSigned);
}