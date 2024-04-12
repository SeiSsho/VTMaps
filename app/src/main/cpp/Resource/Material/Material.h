//
// Created by tts on 4/2/2024.
//

#ifndef VTMAPS_MATERIAL_H
#define VTMAPS_MATERIAL_H

#include "../Texture.h"
#include "../Shader.h"

#include <unordered_map>
#include <vector>
#include <string>

class Material {
    friend class Renderer;
    friend class Sphere;
protected:
    std::shared_ptr<Shader> _shader;
    std::unordered_map<std::string, std::shared_ptr<Texture>> _textures;
    bool _dirty;

public:
    std::shared_ptr<Shader> GetShader();
    std::shared_ptr<Texture> GetTexture(const std::string& textureName);

    virtual void UpdateShader() = 0;

    bool IsDirty() const { return _dirty; }
};


#endif //VTMAPS_MATERIAL_H
