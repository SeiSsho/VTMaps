//
// Created by tts on 4/2/2024.
//

#ifndef VTMAPS_DEFAULTMATERIAL_H
#define VTMAPS_DEFAULTMATERIAL_H


#include "Material.h"

class DefaultMaterial : public Material {
private:
//    Texture* _mainTexture;
    GLuint _mainTexture;
public:
    DefaultMaterial();

    void UpdateShader() override;
};


#endif //VTMAPS_DEFAULTMATERIAL_H
