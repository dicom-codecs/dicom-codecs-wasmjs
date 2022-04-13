cmake_minimum_required(VERSION 3.16)

project (dicomcodecswasmjs LANGUAGES CXX)

# set the build type if not specified
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}")
endif()

# options to control whether or not we build specific libraries.  This allows users to easily add just the codecs they want
option(DICOM_CODECS_BUILD_OPENJPEG "Build OpenJPEG" ON)
option(DICOM_CODECS_BUILD_CHARLS "Build CharLS" ON)
option(DICOM_CODECS_BUILD_LIBJPEGTURBO8 "Build libjpeg-turbo 8 bit" ON)
option(DICOM_CODECS_BUILD_IJG12 "Build IJG 12 bit" ON)
option(DICOM_CODECS_BUILD_RLE "Build RLE" ON)
option(DICOM_CODECS_BUILD_LJPEG6B16 "Build ljpeg-6b 16 bit Codec" ON)
option(DICOM_CODECS_GDCM_JPEG16 "Build GDCM JPEG16 Codec" ON)

# set all projects to build static libraries
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW) # need to explicitly set new behavior for option() to honor normal variables
set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_LIBS ON)

# warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-function -Wno-overloaded-virtual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-return-type")

# do platform specific stuff
SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msimd128")

# BUILD_SHARED_LIBS must be OFF for EMSCRIPTEN builds
option(BUILD_SHARED_LIBS "" OFF)

# add the external library
if(DICOM_CODECS_BUILD_OPENJPEG)
  # NOTE - Add OpenJPEG first since its CMakeLists.txt messes variables up that impact other projects
  add_subdirectory(extern/dicom-codecs EXCLUDE_FROM_ALL)
  # BEGIN - Correct the bugs in the OpenJPEG CMakeLists.txt file here..
  set(EXECUTABLE_OUTPUT_PATH "")
  set(LIBRARY_OUTPUT_PATH "")  
  # END - Correct the bugs in the OpenJPEG CMakeLists.txt file here..
else()
  add_subdirectory(extern/dicom-codecs EXCLUDE_FROM_ALL)
endif(DICOM_CODECS_BUILD_OPENJPEG)



# add the js wrapper
add_subdirectory(src)

# c++ native test case
if(NOT EMSCRIPTEN)
  add_subdirectory(test/cpp)
endif()