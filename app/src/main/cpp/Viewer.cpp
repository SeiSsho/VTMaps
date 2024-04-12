#include "Viewer.h"
#include "Resource/Material/PhongMaterial.h"
#include "Resource/Material/DefaultMaterial.h"


Viewer::Viewer() {

}

Viewer::~Viewer() {
}

void Viewer::Create() {
    _mainCamera =
            std::make_shared<Camera>(100,100,
                                     glm::vec3(0.0,0.0,-8.0),
                                     glm::vec3(0.0),
                                     Camera::Projection::Perspective);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    Material* material = new DefaultMaterial();
    _sphere = std::make_shared<Sphere>(material);

    std::string earthPth;
    if (JNIHelper::ExtractAssetReturnFilename("albedo.png", earthPth)) {
        __android_log_print(ANDROID_LOG_INFO, "FILE", "file %s exist", earthPth.c_str());
        LOG_INFO("EARTH PATH", "%s", earthPth.c_str());
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "FILE", "file %s not found", earthPth.c_str());
    }
    LOG_INFO("EARTH PATH", "%s", earthPth.c_str());
}

void Viewer::Change(int width, int height) {
    _width = width;
    _height = height;
    glViewport(0, 0, width, height);
    float ratio = (float) width / height;
    float left = -ratio;
    float right = ratio;
    float bottom = -1.0f;
    float top = 1.0f;
    float near = 0.0001f;
    float far = 10.0f;

    _mainCamera->SetWidth(width);
    _mainCamera->SetHeight(height);
}

void Viewer::Draw() {
    glClearColor(1.0F, 1.0F, 1.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _sphere->Draw(*_mainCamera.get());
}
