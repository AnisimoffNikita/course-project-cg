#include "renderer.h"

Renderer::Renderer(double scale, int width, int height) :
    scale(scale),
    width(width),
    height(height),
    canvas(width, height, QImage::Format_ARGB32)
{
}

