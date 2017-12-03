#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "sceneobject.h"

class Composite : public SceneObject
{
public:
    Composite();

    virtual void draw(std::unique_ptr<Renderer> &) override;
    virtual void transform(Transformation &) override;
    virtual bool isCamera() override;
    virtual bool isLight() override;
};

#endif // COMPOSITE_H
