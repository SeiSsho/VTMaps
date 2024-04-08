cmake_minimum_required(VERSION 3.22.1)

project("vtmaps")

add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        graphics/GLUtils.h graphics/GLUtils.cpp
        graphics/Matrix.h graphics/Matrix.cpp

        Utilities/JNIHelper.h Utilities/JNIHelper.cpp

        stb_impl.cpp

        Camera.h Camera.cpp
        Image.h Image.cpp
        Mesh.h Mesh.cpp
        Shader.h Shader.cpp
        Sphere.h Sphere.cpp
        Texture.h Texture.cpp
        Transform.h Transform.cpp
        Vertex.h
        Viewer.h Viewer.cpp

        Material/Material.h Material/Material.cpp
        Material/DefaultMaterial.h Material/DefaultMaterial.cpp
        Material/PhongMaterial.h Material/PhongMaterial.cpp

        Image1.h Image1.cpp

        Activities/MainActivity.cpp
)

find_library(log-lib log)

find_package(glm REQUIRED)
find_package(stb REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME}
        glm::glm
        stb::stb
        EGL
        GLESv3
        android
        ${log-lib})