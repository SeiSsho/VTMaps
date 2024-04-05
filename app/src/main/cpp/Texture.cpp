#include "Texture.h"
#include <android/log.h>
#include <android/asset_manager_jni.h>
#include "graphics/GLUtils.h"



Texture::~Texture() {
    if (_id)
        Clean();
}

template<typename T>
void Texture::CreateRenderTexture(const Image<T>& image, const Texture::Setting &setting) {
}

template<typename T>
void Texture::Create2DTexture(const Image<T>& image, const Texture::Setting &setting) {
    _shape = Setting::Shape::Texture2D;
    _numChannel = image.GetNumberChannel();

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    BindImageDataToTexture(image, setting);

    if (setting.MaxMipmapLevel > 0)
        glGenerateMipmap(GL_TEXTURE_2D);

    ConfigureFilterMode(setting);
    ConfigureWrapMode(setting);

    glBindTexture(GL_TEXTURE_2D, 0);
}

template<typename T>
void Texture::CreateCubemap(const Image<T>& image, const Texture::Setting &setting) {
    _shape = Setting::Shape::Cubemap;
}

void Texture::Clean() {
    glDeleteTextures(1, &_id);
}

void Texture::BindTextureUnit(const unsigned int &unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(TextureShapeToGLShape(_shape), _id);
}

GLenum Texture::TextureShapeToGLShape(const Texture::Setting::Shape &shape) {
    switch(shape) {
        case Setting::Shape::Texture2D: return GL_TEXTURE_2D;
        case Setting::Shape::Texture3D: return GL_TEXTURE_3D;
        case Setting::Shape::Cubemap: return GL_TEXTURE_CUBE_MAP;
        case Setting::Shape::Texture2DArray: return GL_TEXTURE_2D_ARRAY;
    }
}

void Texture::ConfigureWrapMode(const Texture::Setting& setting) {
    GLenum target = TextureShapeToGLShape(setting.ShapeType);
    switch (setting.WrapMode)
    {
        case Setting::Wrap::Repeat:
            glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
            if (_shape == Setting::Shape::Cubemap) {
                glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_REPEAT);
            }
            break;
        case Setting::Wrap::ClampToEdge:
            glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            if (_shape == Setting::Shape::Cubemap) {
                glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            }
            break;
    }
}

void Texture::ConfigureFilterMode(const Texture::Setting& setting) {
    GLenum target = TextureShapeToGLShape(setting.ShapeType);
    switch (setting.FilterMode)
    {
        case Setting::Filter::Point:
            glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case Setting::Filter::Bilinear:
            glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        case Setting::Filter::Trilinear:
            glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        case Setting::Filter::Anisotropic:
            break;
    }
}

Texture::Texture(const Image1 &image, const Texture::Setting &setting) {
    switch (setting.ShapeType) {
        case Setting::Shape::Texture2D:
            Create2DTexture(image, setting);
            break;
        default:
            break;
    }
    if (!this->_id) {
        __android_log_print(ANDROID_LOG_ERROR, "TEXTURE", "Create texture failure");
    }
}

void Texture::Create2DTexture(const Image1 &image, const Texture::Setting &setting) {
    _shape = Setting::Shape::Texture2D;
    _numChannel = image.GetNumberChannel();

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    BindImageDataToTexture(image, setting);

    if (setting.MaxMipmapLevel >= 0)
        glGenerateMipmap(GL_TEXTURE_2D);

    ConfigureFilterMode(setting);
    ConfigureWrapMode(setting);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::BindImageDataToTexture(const Image1 &image, const Texture::Setting &setting) {
    GLenum dataFormat;
    switch (_numChannel) {
        case 1:
            _internalFormat = GL_R8;
            dataFormat = GL_RED;
            break;
        case 2:
            _internalFormat = GL_RG8;
            dataFormat = GL_RG;
            break;
        case 3:
            _internalFormat = setting.sRGB ? GL_SRGB8 : GL_RGB8;
            dataFormat = GL_RGB;
            break;
        case 4:
            _internalFormat = setting.sRGB ? GL_SRGB8_ALPHA8 : GL_RGBA8;
            dataFormat = GL_RGBA;
            break;
        default:
//            APP_ERROR("Unsupported texture format!");
            return;
    }
    if (image.GetData() == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "TEXTURE", "Image data is null");
    }

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 _internalFormat,
                 _width, _height,
                 0,
                 dataFormat,
                 GL_UNSIGNED_BYTE,
                 image.GetData());
}

Texture::Texture(const char *path) {
    _id = GLUtils::loadTexture(path);

    glBindTexture(GL_TEXTURE_2D, _id);

    glGenerateMipmap(GL_TEXTURE_2D);

    // Trilinear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);
}

template<typename T>
void Texture::BindImageDataToTexture(const Image<T>& image, const Texture::Setting& setting) {
    GLenum dataFormat;
    switch (_numChannel) {
        case 1:
            _internalFormat = GL_R8;
            dataFormat = GL_RED;
            break;
        case 2:
            _internalFormat = GL_RG8;
            dataFormat = GL_RG;
            break;
        case 3:
            _internalFormat = setting.sRGB ? GL_SRGB8 : GL_RGB8;
            dataFormat = GL_RGB;
            break;
        case 4:
            _internalFormat = setting.sRGB ? GL_SRGB8_ALPHA8 : GL_RGBA8;
            dataFormat = GL_RGBA;
            break;
        default:
//            APP_ERROR("Unsupported texture format!");
            return;
    }

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 _internalFormat,
                 _width, _height,
                 0,
                 dataFormat,
                 (std::is_same<T, unsigned char>::value) ? GL_UNSIGNED_BYTE : GL_FLOAT,
                 image.GetData());
}

template<typename T>
Texture::Texture(const Image<T> &image, const Texture::Setting &setting) {
    switch (setting.ShapeType) {
        case Setting::Shape::Texture2D:
            Create2DTexture(image, setting);
            break;
        case Setting::Shape::Cubemap:
            CreateCubemap(image, setting);
            break;
        default:
            break;
    }
}
