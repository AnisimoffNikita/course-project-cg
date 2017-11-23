#include "renderer.h"

Renderer::Renderer(float scale, int width, int height) :
    scale(scale),
    width(width),
    height(height),
    canvas(width, height, QImage::Format_ARGB32)
{
}

