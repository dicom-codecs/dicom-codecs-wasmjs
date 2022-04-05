
add_executable(dicomcodecswasm ${SOURCES} jslib.cpp)
target_link_libraries(dicomcodecswasm PRIVATE dicomcodecs)
target_compile_features(dicomcodecswasm PUBLIC cxx_std_17)

set_target_properties(
    dicomcodecswasm 
    PROPERTIES 
    LINK_FLAGS "\
    -O3 \
    -lembind \
    -s DISABLE_EXCEPTION_CATCHING=1 \
    -s ASSERTIONS=0 \
    -s NO_EXIT_RUNTIME=1 \
    -s MALLOC=emmalloc \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s INITIAL_MEMORY=50MB \
    -s FILESYSTEM=0 \
    -s EXPORTED_FUNCTIONS=[] \
    -s EXPORTED_RUNTIME_METHODS=[ccall] \
")
