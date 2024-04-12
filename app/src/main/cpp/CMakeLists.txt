cmake_minimum_required(VERSION 3.22.1)

project("vtmaps")

add_library(${CMAKE_PROJECT_NAME} SHARED
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
        Transform.h Transform.cpp
        Vertex.h
        Viewer.h Viewer.cpp

        Resource/Material/Material.h Resource/Material/Material.cpp
        Resource/Material/DefaultMaterial.h Resource/Material/DefaultMaterial.cpp
        Resource/Material/PhongMaterial.h Resource/Material/PhongMaterial.cpp


        jniCalls/MainActivity.cpp
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