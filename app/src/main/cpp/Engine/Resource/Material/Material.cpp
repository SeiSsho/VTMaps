#include "Material.h"

std::shared_ptr<Shader> Engine::Resource::Material::GetShader() const {
#ifndef NDEBUG
    if (!_shader.get()) {
        LOG_ERROR("MATERIAL", "Shader isn' initialized");
    }
#endif
    return _shader;
}

std::shared_ptr<Texture> Engine::Resource::Material::GetTexture(std::string &name) {
    auto it = _textures.find(name);
    if (it != _textures.end())
        return it->second;
    LOG_ERROR("MATERIAL", "No texture name %s in material", name.c_str());
    return nullptr;
}

void Engine::Resource::Material::SetPriority(const int &priority) {
    _priority = priority;
}

int Engine::Resource::Material::GetPriority() const {
    return _priority;
}
