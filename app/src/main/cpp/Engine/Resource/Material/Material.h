//
// Created by tts on 4/19/2024.
//

#ifndef VTMAPS_MATERIAL_H
#define VTMAPS_MATERIAL_H

#include <memory>
#include <unordered_map>
#include <string>

#include "../Shader.h"
#include "../Texture.h"
#include "../../Utility/Logger.h"

namespace Engine::Resource {
    class Material {
    private:
        std::shared_ptr<Shader> _shader;
        std::unordered_map<std::string, std::shared_ptr<Texture>> _textures;
        int _priority;

    public:
        ~Material() = default;

        virtual void Update() = 0;

        std::shared_ptr<Shader> GetShader() const;
        std::shared_ptr<Texture> GetTexture(std::string& name);

        void SetPriority(const int& priority);
        int GetPriority() const;
    };
}



#endif //VTMAPS_MATERIAL_H
