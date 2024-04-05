//
// Created by tts on 4/2/2024.
//

#ifndef VTMAPS_PHONGMATERIAL_H
#define VTMAPS_PHONGMATERIAL_H


#include "Material.h"

class PhongMaterial : public Material {
public:
    PhongMaterial();

    void UpdateShader() override;
};


#endif //VTMAPS_PHONGMATERIAL_H
