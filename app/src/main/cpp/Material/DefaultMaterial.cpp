//
// Created by tts on 4/2/2024.
//

#include "DefaultMaterial.h"
#include <android/log.h>
#include <filesystem>
#include <android/asset_manager.h>
#include "../graphics/GLUtils.h"

DefaultMaterial::DefaultMaterial() {
    _shader = Shader::CreateDefaultShader();
    _dirty = false;
//    Image1 earthImage("C:\\Users\\tts\\Desktop\\VTMaps\\app\\src\\main\\res\\8k_earth_daymap.jpg");
    // Image1 earthImage("file://android_asset/8k_earth_daymap.jpg");
//    std::filesystem::path p("file://android_asset/8k_earth_daymap.jpg");
//    if (std::filesystem::exists(p) && std::filesystem::is_regular_file(p)) {
//        __android_log_print(ANDROID_LOG_INFO, "FILE", "valid path");
//    } else {
//        __android_log_print(ANDROID_LOG_ERROR, "FILE", "invalid path");
//    }
//    Texture::Setting textureSetting {
//            .FlipVertical = true,
//            .sRGB = false,
//            .AlphaIsTransparency = false,
//            .IsGenerateMipmaps = false,
//            .MaxWidth = 0,
//            .MaxHeight = 0,
//            .SwizzleSetting = {Texture::Setting::Swizzle::Red, Texture::Setting::Swizzle::Green, Texture::Setting::Swizzle::Blue, Texture::Setting::Swizzle::Zero},
//            .MaxMipmapLevel = 0,
//            .BorderColor = glm::vec4(1.0),
//            .MipmapFilteringMode = Texture::Setting::MipmapFiltering::Box,
//            .ShapeType = Texture::Setting::Shape::Texture2D,
//            .TextureType = Texture::Setting::Type::Default,
//            .FilterMode = Texture::Setting::Filter::Trilinear,
//            .WrapMode = Texture::Setting::Wrap::ClampToEdge,
//            .alphaSrc = Texture::Setting::AlphaSource::Alpha,
//            .resizeAlgorithm = Texture::Setting::ResizeAlgorithm::Default,
//    };
//    _mainTexture = new Texture(earthImage, textureSetting);
_mainTexture = GLUtils::loadTexture("8k_earth_daymap.jpg");
    _shader->Bind();
    _shader->SetInt("uTexture", 0);
    _shader->Unbind();
}

void DefaultMaterial::UpdateShader() {
//    _mainTexture->BindTextureUnit(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _mainTexture);
//    glBindTexture(GL_TEXTURE_2D, _mainTexture->GetId());
    glUniform1i(glGetUniformLocation(_shader->GetId(), "uTexture"), 0);
}
