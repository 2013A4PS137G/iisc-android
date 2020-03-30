# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

include_directories(
        include
        include/kaldi
        include/openfst
        include/libsvm)

add_definitions(-DHAVE_CLAPACK)

add_library( # Sets the name of the library.
        asthma-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/asthma-predict.cpp
        src/main/cpp/compute-mfcc-feats.cpp
        src/main/cpp/feat-util.cpp
        src/main/cpp/kaldi/base/io-funcs.cc
        src/main/cpp/kaldi/base/kaldi-error.cc
        src/main/cpp/kaldi/base/kaldi-math.cc
        src/main/cpp/kaldi/base/kaldi-utils.cc
        src/main/cpp/kaldi/base/timer.cc
        src/main/cpp/kaldi/feat/feature-functions.cc
        src/main/cpp/kaldi/feat/feature-mfcc.cc
        src/main/cpp/kaldi/feat/feature-window.cc
        src/main/cpp/kaldi/feat/mel-computations.cc
        src/main/cpp/kaldi/feat/resample.cc
        src/main/cpp/kaldi/feat/wave-reader.cc
        src/main/cpp/kaldi/matrix/compressed-matrix.cc
        src/main/cpp/kaldi/matrix/kaldi-matrix.cc
        src/main/cpp/kaldi/matrix/kaldi-vector.cc
        src/main/cpp/kaldi/matrix/matrix-functions.cc
        src/main/cpp/kaldi/matrix/optimization.cc
        src/main/cpp/kaldi/matrix/packed-matrix.cc
        src/main/cpp/kaldi/matrix/qr.cc
        src/main/cpp/kaldi/matrix/sp-matrix.cc
        src/main/cpp/kaldi/matrix/sparse-matrix.cc
        src/main/cpp/kaldi/matrix/srfft.cc
        src/main/cpp/kaldi/matrix/tp-matrix.cc
        src/main/cpp/kaldi/transform/cmvn.cc
        src/main/cpp/kaldi/util/kaldi-holder.cc
        src/main/cpp/kaldi/util/kaldi-io.cc
        src/main/cpp/kaldi/util/kaldi-semaphore.cc
        src/main/cpp/kaldi/util/kaldi-table.cc
        src/main/cpp/kaldi/util/parse-options.cc
        src/main/cpp/kaldi/util/simple-io-funcs.cc
        src/main/cpp/kaldi/util/text-utils.cc
        src/main/cpp/kaldi/ivector/voice-activity-detection.cc
        src/main/cpp/kaldi/ivectorbin/compute-vad.cc
        src/main/cpp/libsvm/svm-predict.c
        src/main/cpp/libsvm/svm.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

add_library(lapack
        STATIC
        IMPORTED)

add_library(blas
        STATIC
        IMPORTED)

add_library(clapack
        STATIC
        IMPORTED)

add_library(f2c
        STATIC
        IMPORTED)

add_library(openblas
        STATIC
        IMPORTED)



set_target_properties(lapack
        PROPERTIES
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/src/main/cpp/libs/${ANDROID_ABI}/liblapack.a)

set_target_properties(blas
        PROPERTIES
        IMPORTED_LOCATION  ${PROJECT_SOURCE_DIR}/src/main/cpp/libs/${ANDROID_ABI}/libblas.a)

set_target_properties(clapack
        PROPERTIES
        IMPORTED_LOCATION  ${PROJECT_SOURCE_DIR}/src/main/cpp/libs/${ANDROID_ABI}/libclapack.a)

set_target_properties(f2c
        PROPERTIES
        IMPORTED_LOCATION  ${PROJECT_SOURCE_DIR}/src/main/cpp/libs/${ANDROID_ABI}/libf2c.a)

set_target_properties(openblas
        PROPERTIES
        IMPORTED_LOCATION  ${PROJECT_SOURCE_DIR}/src/main/cpp/libs/${ANDROID_ABI}/libopenblas.a)


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        asthma-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        clapack
        lapack
        blas
        f2c
        openblas
        )