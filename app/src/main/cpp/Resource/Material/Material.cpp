//
// Created by tts on 4/2/2024.
//

#include "Material.h"

std::shared_ptr<Shader> Material::GetShader() {
    return _shader;
}

std::shared_ptr<Texture> Material::GetTexture(const std::string &textureName) {
    _textures.find(textureName) == _textures.end() ? nullptr : _textures[textureName];
}
