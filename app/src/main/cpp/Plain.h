//
// Created by tts on 4/5/2024.
//

#ifndef VTMAPS_PLAIN_H
#define VTMAPS_PLAIN_H

#include "Material/Material.h"
#include <memory>

class Plain {
private:
    std::shared_ptr<Material> _material;
    GLuint _vao, _vbo, _ebo;
public:
    Plain();
    ~Plain();

    void Render();

private:
};


#endif //VTMAPS_PLAIN_H
