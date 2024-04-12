//
// Created by tts on 4/4/2024.
//

#ifndef VTMAPS_IMAGE1_H
#define VTMAPS_IMAGE1_H

#include "Image.h"
#include "../Utilities/Logger.h"

class Image1 {
private:
    int _width, _height, _numChannel;
    unsigned char*  _data;

public:
    /// \brief
    /// \param path Path to image source, just check becareful before set, no handle exception
    /// \param isFlipVertical Should  vertical flip the image
    /// \param desiredChannel 0: Automatical set by source image
    /// \note If image's channel is lower than desired, the fake channel will have default value (255 or 255.0)
    Image1 (const char* path,
           bool        isFlipVertical = true,
           int         desiredChannel = 0);

    ~Image1();

    // Clamp Edge is default
    void ResizeImage(int newWidth, int newHeight, ResizeAlgorithm resizeAlgorithm = ResizeAlgorithm::Default);

    /// Extension will be add automatically
    ///
    /// TODO: support .hdr
    void WriteToFile(const std::string& path, Extension extension);

    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }
    int GetNumberChannel() const { return _numChannel; }
    unsigned char *  GetData() const { return _data; }

private:
    void ReadImageData(const char* path);
    void ModifyNumberChannelIfNeeded();
};


#endif //VTMAPS_IMAGE1_H
