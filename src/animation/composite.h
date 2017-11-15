#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "sceneobject.h"

class Composite : public SceneObject
{
public:
    Composite();

    virtual void draw(Render &render) override;
    virtual void transform(const Transformation &transformation) override;
    virtual bool isCamera() override;
    virtual bool isLight() override;
};

#endif // COMPOSITE_H
