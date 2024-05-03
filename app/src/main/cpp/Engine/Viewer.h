#ifndef VTMAPS_VIEWER_H
#define VTMAPS_VIEWER_H

#include "Camera.h"
#include "Core.h"
#include <memory>

namespace Engine {
    class Viewer {
        std::unique_ptr<Camera> _mainCamera;
//        std::shared_ptr<Sphere> _sphere;
        int _width, _height;

    public:
        Viewer();
        ~Viewer();

        void Create();
        void Change(int width, int height);
        void Draw();
    };
}

#endif //VTMAPS_VIEWER_H
