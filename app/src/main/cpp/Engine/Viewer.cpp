//
// Created by tts on 4/19/2024.
//

#include "Viewer.h"

namespace Engine {
    Viewer::Viewer() {

    }

    Viewer::~Viewer() {

    }

    void Viewer::Create() {
//        _mainCamera = std::make_unique<Camera>(1, 1, );
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
    }

    void Viewer::Change(int width, int height) {
        glViewport(0, 0, width, height);
    }

    void Viewer::Draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

