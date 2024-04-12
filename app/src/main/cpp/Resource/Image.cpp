#include "Image.h"

template Image<unsigned char>::Image (const char* path, bool isFlipVertical, int desiredChannel);
template Image<float>::Image (const char* path, bool isFlipVertical, int desiredChannel);
template <typename T>
Image<T>::Image(const char* path, bool isFlipVertical, int desiredChannel)
        : _numChannel(desiredChannel) {
    stbi_set_flip_vertically_on_load(isFlipVertical);
    ModifyNumberChannelIfNeeded();
    ReadImageData(path);
}

template Image<unsigned char>::~Image();
template Image<float>::~Image();
template <typename T>
Image<T>::~Image() {
    free(_data);
}

template<>
void Image<unsigned char>::ResizeImage(int newWidth, int newHeight, ResizeAlgorithm resizeAlgorithm) {
    if (!(newWidth && newHeight)) {
//        ENGINE_WARN("Size must have value higher than 0! Not resize image.")
        return;
    }
    unsigned char* newData = (unsigned char*) malloc(newWidth * newHeight * _numChannel * sizeof(unsigned char));
    stbir_resize_uint8(_data, _width, _height, 0,
                       newData, newWidth, newHeight, 0, _numChannel);
    free(_data);
    //////////////////////////////////////////////////////////////////
    //// ?	 Nên gán trực tiếp hay xử dụng memcpy như dưới đây	  ////
    // _data = newData
    // hoặc
    _data = (unsigned char*) malloc(newWidth * newHeight * _numChannel * sizeof(unsigned char));
    memcpy(_data, newData, newWidth * newHeight * _numChannel * sizeof(unsigned char));
    free(newData);
    //////////////////////////////////////////////////////////////////
    _width = newWidth;
    _height = newHeight;
}

template<>
void Image<float>::ResizeImage(int newWidth, int newHeight, ResizeAlgorithm resizeAlgorithm) {
    if (!(newWidth && newHeight)) {
//        ENGINE_WARN("Size must have value higher than 0! Not resize image.")
        return;
    }
    float* newData = (float*) malloc(newWidth * newHeight * _numChannel * sizeof(float));
    stbir_resize_float(_data, _width, _height, 0,
                       newData, newWidth, newHeight, 0, _numChannel);
    free(_data);
    //////////////////////////////////////////////////////////////////
    //// ?	 Nên gán trực tiếp hay xử dụng memcpy như dưới đây	  ////
    // _data = newData
    // hoặc
    _data = (float*) malloc(newWidth * newHeight * _numChannel * sizeof(float));
    memcpy(_data, newData, newWidth * newHeight * _numChannel * sizeof(float));
    free(newData);
    //////////////////////////////////////////////////////////////////
    _width = newWidth;
    _height = newHeight;
}


template void Image<float>::WriteToFile(const std::string& path, Extension extension);
template void Image<unsigned char>::WriteToFile(const std::string& path, Extension extension);
template<typename T>
void Image<T>::WriteToFile(const std::string& path, Extension extension) {
    std::string filePath(path);
    switch (extension) {
        case Extension::Png:
            filePath += ".png";
            stbi_write_png(filePath.c_str(), _width, _height, _numChannel, _data,
                           _width * _numChannel);
            break;
        case Extension::Bmp:
            filePath += ".bmp";
            stbi_write_bmp(filePath.c_str(), _width, _height, _numChannel, _data);
            break;
        case Extension::Jpg:
            filePath += ".jpg";
            stbi_write_jpg(filePath.c_str(), _width, _height, _numChannel, _data,
                           100);
            break;
        case Extension::Tga:
            filePath += ".tga";
            stbi_write_tga(filePath.c_str(), _width, _height, _numChannel, _data);
            break;
    }
}

template<> void Image<unsigned char>::ReadImageData(const char* path) {
    _data = stbi_load(path, &_width, &_height, nullptr, _numChannel);
}

template<> void Image<float>::ReadImageData(const char* path) {
    _data = stbi_loadf(path, &_width, &_height, nullptr, _numChannel);
}

template <typename T>
void Image<T>::ModifyNumberChannelIfNeeded() {
    if (_numChannel > IMAGE_MAX_NUMBER_CHANNEL_SUPPORTED) {
//        ENGINE_WARN("[IMAGE] Not support higher 4 channel color, load default (4 channels)")
        _numChannel = IMAGE_MAX_NUMBER_CHANNEL_SUPPORTED;
    }
}