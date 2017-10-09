#ifndef GRAYSCALEIMAGE_H
#define GRAYSCALEIMAGE_H

#include <QImage>

#include <memory>
#include "imagebase.h"

#include "src/number.h"
#include "grayscalecolor.h"

class ImageConverter;

class GrayscaleImage : public ImageBase<uint8>
{
public:
    using ImageBase<uint8>::ImageBase;

    friend class ImageConverter;
    friend class GrayscaleConverter;
};



#endif // GRAYSCALEIMAGE_H
