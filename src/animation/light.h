#ifndef LIGHT_H
#define LIGHT_H

#include "sceneobject.h"

class Light : public SceneObject
{
public:
    Light();

    virtual void draw(Render &render) override;
    virtual void transform(const Transformation &transformation) override;
    virtual bool isCamera() override;
    virtual bool isLight() override;
};

#endif // LIGHT_H
