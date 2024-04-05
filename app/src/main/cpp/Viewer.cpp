#include "Viewer.h"
#include "Material/PhongMaterial.h"
#include "Material/DefaultMaterial.h"
#include "graphics/GLUtils.h"

Viewer::Viewer() {
    Material* material = new DefaultMaterial();
    _sphere = std::make_shared<Sphere>(material);
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

Viewer *viewer;

extern "C"
JNIEXPORT void JNICALL
Java_com_thanhdo_vtmaps_MainRenderer_SurfaceCreate(JNIEnv *env,
                                                   jclass type,
                                                   jobject assetManager) {
    GLUtils::setEnvAndAssetManager(env, assetManager);
    if (viewer) {
        delete viewer;
        viewer = NULL;
    }
    viewer = new Viewer();
    viewer->Create();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_thanhdo_vtmaps_MainRenderer_SurfaceChange(JNIEnv *env,
                                                     jclass type,
                                                     jint width,
                                                     jint height) {
    if (viewer) {
        viewer->Change(width, height);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_thanhdo_vtmaps_MainRenderer_DrawFrame(JNIEnv *env, jclass type) {
    if (viewer) {
        viewer->Draw();
    }
}
