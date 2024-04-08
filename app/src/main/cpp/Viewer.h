#ifndef VTMAPS_VIEWER_H
#define VTMAPS_VIEWER_H

#include <memory>
#include "Camera.h"
#include "Sphere.h"
#include "Utilities/JNIHelper.h"



class Viewer {
private:
    std::shared_ptr<Camera> _mainCamera;
    std::shared_ptr<Sphere> _sphere;
    int _width, _height;

public:
    Viewer();
    ~Viewer();

    void Create();
    void Change(int width, int height);
    void Draw();
};


#endif //VTMAPS_VIEWER_H
