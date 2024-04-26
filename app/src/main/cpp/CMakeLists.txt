cmake_minimum_required(VERSION 3.22.1)

project("vtmaps")

set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../third-party)

add_library(amanithvg SHARED IMPORTED)
set_target_properties(amanithvg PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/amanithvg/lib/android/${ANDROID_ABI}/gle/standalone/libAmanithVG.so)

add_library(gmath STATIC IMPORTED)
set_target_properties(gmath PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/gmath/lib/${ANDROID_ABI}/libgmath.a)

add_library(gperf SHARED IMPORTED)
set_target_properties(gperf PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/gperf/lib/${ANDROID_ABI}/libgperf.so)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -DENGINE_GLE=1")

add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp
        # Implement stb library
        stb_impl.cpp
        adder.h adder.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${distribution_DIR}/amanithvg/include
        ${distribution_DIR}/gmath/include
        ${distribution_DIR}/gperf/include)

find_library(log-lib log)

find_package(glm REQUIRED)
find_package(stb REQUIRED)
find_package(magic_enum REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME}
        amanithvg
        gmath
        gperf
        glm::glm
        stb::stb
        magic_enum::magic_enum
        EGL
        GLESv3
        android
        ${log-lib})

##################################### UNIT TEST ################################
# NOTE: Can i separate this unit test in another CMakeLists.txt file ?
project("app_tests")
find_package(googletest REQUIRED CONFIG)
find_package(junit-gtest REQUIRED CONFIG)

add_library(app_tests SHARED "Unit Test/test.cpp")

# if third-party libraries must include, don't need if library provided by Conan
include_directories(${distribution_DIR}/amanithvg/include
        ${distribution_DIR}/gmath/include
        ${distribution_DIR}/gperf/include)

target_link_libraries(app_tests
        PRIVATE
        vtmaps
        googletest::gtest
        junit-gtest::junit-gtest
)
