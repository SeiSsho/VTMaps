#ifndef VTMAPS_TEXTURE_H
#define VTMAPS_TEXTURE_H

#include "../Core.h"

namespace Engine {
    class Texture {
    public:
        struct Parameter;
    private:
        GLint _id;
    public:

    };

    struct Texture::Parameter {
        enum class Swizzle {
            Red, Green, Blue,
            Zero, One,
            OneMinusRed, OneMinusGreen, OneMinusBlue
        };

        enum class Wrap {
            Repeat,
            MirrorRepeat,
            ClampToEdge,
            ClampToBorder
        };

        enum class Filter {
            Point,
            Bilinear,
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
    };
}

#endif //VTMAPS_TEXTURE_H
