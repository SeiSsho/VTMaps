//
// Created by tts on 4/2/2024.
//

#include "DefaultMaterial.h"
#include <android/log.h>
#include <filesystem>
#include <android/asset_manager.h>

DefaultMaterial::DefaultMaterial() {
    _shader = Shader::CreateDefaultShader();
    _dirty = false;
    std::string imagePath;
    JNIHelper::ExtractAssetReturnFilename("8k_earth_daymap.jpg", imagePath);
    Image1 earthImage(imagePath.c_str());
    Texture::Setting textureSetting {
            .FlipVertical = true,
            .sRGB = false,
            .AlphaIsTransparency = false,
            .IsGenerateMipmaps = false,
            .MaxWidth = 0,
            .MaxHeight = 0,
            .SwizzleSetting = {Texture::Setting::Swizzle::Red, Texture::Setting::Swizzle::Green, Texture::Setting::Swizzle::Blue, Texture::Setting::Swizzle::Zero},
            .MaxMipmapLevel = 0,
            .BorderColor = glm::vec4(1.0),
            .MipmapFilteringMode = Texture::Setting::MipmapFiltering::Box,
            .ShapeType = Texture::Setting::Shape::Texture2D,
            .TextureType = Texture::Setting::Type::Default,
            .FilterMode = Texture::Setting::Filter::Trilinear,
            .WrapMode = Texture::Setting::Wrap::ClampToEdge,
            .alphaSrc = Texture::Setting::AlphaSource::Alpha,
            .resizeAlgorithm = Texture::Setting::ResizeAlgorithm::Default,
    };
    _textures["mainTexture"] = std::make_shared<Texture>(earthImage, textureSetting);
    _shader->Bind();
    _shader->SetInt("uTexture", 0);
    _shader->Unbind();
}

void DefaultMaterial::UpdateShader() {
//    _mainTexture->BindTextureUnit(0);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, _mainTexture);
    if (std::shared_ptr<Texture> t = GetTexture("mainTexture")) {
        t->BindTextureUnit(0);
    }
//    glBindTexture(GL_TEXTURE_2D, _mainTexture->GetId());
    glUniform1i(glGetUniformLocation(_shader->GetId(), "uTexture"), 0);
}
