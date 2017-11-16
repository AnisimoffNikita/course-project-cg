#include "renderer.h"

#include "commontransformation.h"

#include <QPainter>

Renderer::Renderer(double scale, int32 width, int32 height) :
    scale(scale),
    width(width),
    height(height)
{
}

