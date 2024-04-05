#ifndef VTMAPS_TEXTURE_H
#define VTMAPS_TEXTURE_H

#include <glm/glm.hpp>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <GLES3/gl3ext.h>
#include <jni.h>

#include "Image.h"
#include "Image1.h"

class Texture {
public:
    struct Setting {
        enum class Swizzle {
            Red, Green, Blue,
            Zero, One,
            OneMinusRed, OneMinusGreen, OneMinusBlue
        };

        enum class Wrap {
            Repeat,
            ClampToEdge,
        };

        enum class Filter {
            Point,
            Bilinear, // Linear
            Trilinear,
            Anisotropic,

            Linear = Bilinear
        };

        enum class Shape {
            Texture2D,
            Cubemap,
            Texture3D,
            Texture2DArray
        };

        enum class AlphaSource {
            None, Alpha, GrayScale
        };

        enum class Type {
            Default,
            Normal,
            SingleChannel
        };

        enum class MappingCube {
            Cylindrical,
            Supported,
            CibicEnvironment,
            SphereMap
        };

        enum class ResizeAlgorithm {
            Point,
            Bilinear,
            Supported,
            DownSample,
            Mitchell,
            UpSample,
            Bicubic,
            CatmullRom,

            Default = Point
        };

        enum class MipmapFiltering {
            Box, Supported, Kaiser
        };

        bool            FlipVertical;
        bool            sRGB;
        bool            AlphaIsTransparency;
        bool            IsGenerateMipmaps;
        unsigned int    MaxWidth;
        unsigned int    MaxHeight;
        Swizzle         SwizzleSetting[4];
        unsigned int    MaxMipmapLevel;
        glm::vec4       BorderColor;
        MipmapFiltering MipmapFilteringMode;
        Shape           ShapeType;
        Type            TextureType;
        Filter          FilterMode;
        Wrap            WrapMode;
        AlphaSource     alphaSrc;
        ResizeAlgorithm resizeAlgorithm;
    };

private:
    GLuint _id;
    int _width, _height, _numChannel;
    GLuint _internalFormat;
    Setting::Shape _shape;

public:
    template<typename T>
    Texture(const Image<T>& image, const Setting& setting);
    Texture(const char* path);
    ~Texture();

    Texture(const Image1& image, const Setting& setting);
    void Create2DTexture(const Image1& image, const Setting& setting);

    const GLuint& GetId() const { return _id; }

    template<typename T>
    void CreateRenderTexture(const Image<T>& image, const Setting& setting);
    template<typename T>
    void Create2DTexture(const Image<T>& image, const Setting& setting);
    template<typename T>
    void CreateCubemap(const Image<T>& image, const Setting& setting);

    void Clean();
    void BindTextureUnit(const unsigned int& unit);

    static GLenum TextureShapeToGLShape(const Setting::Shape& shape);

protected:
    void ConfigureWrapMode(const Texture::Setting& setting);
    void ConfigureFilterMode(const Texture::Setting& setting);
    template<typename T>
    void BindImageDataToTexture(const Image<T>& image, const Texture::Setting& setting);
    void BindImageDataToTexture(const Image1& image, const Texture::Setting& setting);
};


#endif //VTMAPS_TEXTURE_H
