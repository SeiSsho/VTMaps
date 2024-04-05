//
// Created by tts on 4/4/2024.
//

#include "Image1.h"
#include <android/log.h>

Image1::Image1(const char *path, bool isFlipVertical, int desiredChannel) {
    stbi_set_flip_vertically_on_load(isFlipVertical);
    ModifyNumberChannelIfNeeded();
    ReadImageData(path);
}

Image1::~Image1() {
    free(_data);
}

void Image1::ResizeImage(int newWidth, int newHeight, ResizeAlgorithm resizeAlgorithm) {
    unsigned char* newData = (unsigned char*) malloc(newWidth * newHeight * _numChannel * sizeof(unsigned char));
    stbir_resize_uint8(_data, _width, _height, 0,
                       newData, newWidth, newHeight, 0, _numChannel);
//    free(_data);
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

void Image1::WriteToFile(const std::string &path, Extension extension) {
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

void Image1::ReadImageData(const char *path) {
    _data = stbi_load(path, &_width, &_height, nullptr,
                                                       _numChannel);
    if (!_data)
        __android_log_print(ANDROID_LOG_ERROR, "IMAGE", "READ IMAGE FAILURE");
}

void Image1::ModifyNumberChannelIfNeeded() {
    if (_numChannel > IMAGE_MAX_NUMBER_CHANNEL_SUPPORTED) {
        _numChannel = IMAGE_MAX_NUMBER_CHANNEL_SUPPORTED;
    }
}
