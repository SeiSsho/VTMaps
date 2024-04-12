//
// Created by tts on 4/2/2024.
//

#include "PhongMaterial.h"

PhongMaterial::PhongMaterial()
{
    _dirty = false;
    _shader = Shader::CreatePhongShader();
}

void PhongMaterial::UpdateShader() {
    GetTexture("Ambient")->BindTextureUnit(0);
    _shader->SetInt("uAmbient", 0);

    GetTexture("Specular")->BindTextureUnit(1);
    _shader->SetInt("uSpecular", 1);

    GetTexture("Diffuse")->BindTextureUnit(2);
    _shader->SetInt("uDiffuse", 2);
}
