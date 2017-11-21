#ifndef LIGHT_H
#define LIGHT_H

#include "sceneobject.h"

class Light : public SceneObject
{
public:
    Light() = default;
    Light(const Vertex &position, double intensity);
    virtual ~Light() = default;

    virtual void draw(std::unique_ptr<Renderer> &) override;
    virtual void transform(const Transformation &transformation) override;
    virtual bool isCamera() override;
    virtual bool isLight() override;

    virtual double getIntensity(const Vertex &normal) const = 0;

protected:
    double intensity;
};

using SharedLight = std::shared_ptr<Light>;
using WeakLight = std::weak_ptr<Light>;


#endif // LIGHT_H
