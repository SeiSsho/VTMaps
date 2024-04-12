#ifndef VTMAPS_IMAGE_H
#define VTMAPS_IMAGE_H

#include <filesystem>

#include <stb_image_resize.h>
#include <stb_image_write.h>
#include <stb_image.h>
#include <type_traits>
#include <exception>

#ifndef IMAGE_MAX_NUMBER_CHANNEL_SUPPORTED
#define IMAGE_MAX_NUMBER_CHANNEL_SUPPORTED 4
#endif

// Region Utilites
#pragma region utilities
enum class Extension {
    Png, Jpg, Bmp, Tga
};
enum class ResizeAlgorithm {
    Default, Box, Triangle, CubicSpline, CatmullRom, Mitchell
};
static stbir_filter ResizeAlgorithmToStbirFilter(ResizeAlgorithm algorithm) {
    switch(algorithm) {
        case ResizeAlgorithm::Box:			return STBIR_FILTER_BOX;
        case ResizeAlgorithm::Triangle:		return STBIR_FILTER_TRIANGLE;
        case ResizeAlgorithm::CubicSpline:	return STBIR_FILTER_CUBICBSPLINE;
        case ResizeAlgorithm::CatmullRom:	return STBIR_FILTER_CATMULLROM;
        case ResizeAlgorithm::Mitchell:		return STBIR_FILTER_MITCHELL;
        default:                            return STBIR_FILTER_DEFAULT;
    }
}
#pragma endregion
// End Region

/// \brief Can anyone help me at scope T in 2 types below
/// \tparam T unsigned char, float
template <typename T>
class Image {
private:
    int _width, _height, _numChannel;
    T*  _data;

public:
    /// \brief
    /// \param path Path to image source, just check becareful before set, no handle exception
    /// \param isFlipVertical Should  vertical flip the image
    /// \param desiredChannel 0: Automatical set by source image
    /// \note If image's channel is lower than desired, the fake channel will have default value (255 or 255.0)
    Image (const char* path,
           bool        isFlipVertical = true,
           int         desiredChannel = 0);

    ~Image();

    // Clamp Edge is default
    void ResizeImage(int newWidth, int newHeight, ResizeAlgorithm resizeAlgorithm = ResizeAlgorithm::Default);

    /// Extension will be add automatically
    ///
    /// TODO: support .hdr
    void WriteToFile(const std::string& path, Extension extension);

    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }
    int GetNumberChannel() const { return _numChannel; }
    T*  GetData() const { return _data; }

private:
    void ReadImageData(const char* path);
    void ModifyNumberChannelIfNeeded();
};

#endif //VTMAPS_IMAGE_H
