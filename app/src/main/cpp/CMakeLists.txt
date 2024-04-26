cmake_minimum_required(VERSION 3.22.1)

project("vtmaps")

set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../third-party)

add_library(amanithvg SHARED IMPORTED)
set_target_properties(amanithvg PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/amanithvg/lib/android/${ANDROID_ABI}/gle/standalone/libAmanithVG.so)

#find_package(amanithvg REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -DENGINE_GLE=1")

add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp
        # Utilities
        Utilities/JNIHelper.h Utilities/JNIHelper.cpp
        Utilities/Logger.h

        # Implement stb library
        stb_impl.cpp

        Camera.h Camera.cpp
        Resource/Image.h Resource/Image.cpp
        Resource/Image1.h Resource/Image1.cpp
        Mesh.h Mesh.cpp
        Resource/Shader.h Resource/Shader.cpp
        Sphere.h Sphere.cpp
        Resource/Texture.h Resource/Texture.cpp
        Vertex.h
        Viewer.h Viewer.cpp

        Resource/Material/Material.h Resource/Material/Material.cpp
        Resource/Material/DefaultMaterial.h Resource/Material/DefaultMaterial.cpp
        Resource/Material/PhongMaterial.h Resource/Material/PhongMaterial.cpp


        jniCalls/MainActivity.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${distribution_DIR}/amanithvg/include)

find_library(log-lib log)

find_package(glm REQUIRED)
find_package(stb REQUIRED)
find_package(magic_enum REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME}
        amanithvg
        glm::glm
        stb::stb
        magic_enum::magic_enum
        EGL
        GLESv3
        android
        ${log-lib})


find_package(googletest REQUIRED CONFIG)
find_package(junit-gtest REQUIRED CONFIG)

add_library(adder OBJECT adder.cpp)

add_library(app_tests SHARED "Unit Test/test.cpp")
#add_library(app_test SHARED glm)
find_package(glm REQUIRED)

target_link_libraries(app_tests
        PRIVATE
        $<TARGET_OBJECTS:adder>
        glm::glm
        googletest::gtest
        junit-gtest::junit-gtest
)
