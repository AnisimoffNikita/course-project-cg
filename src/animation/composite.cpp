#include "composite.h"

Composite::Composite()
{
}


void Composite::draw(std::unique_ptr<Renderer> &)
{
}

void Composite::transform(Transformation &)
{
}

bool Composite::isCamera()
{
    return false;
}

bool Composite::isLight()
{
    return false;
}
