#ifndef MESHDATA_H
#define MESHDATA_H

#include "src/image/color.h"
#include "src/math/vec3.h"
#include "src/number.h"
#include <array>
#include "transformation.h"

using namespace std;

class Vertex
{
public:
    Vertex() = default;
    Vertex(const Vec3 v, const Vec3 n);

    const Vec3 &getV() const;
    void setV(const Vec3 &value);

    const Vec3 &getN();
    void setN(const Vec3 &value);

    void transform(const Transformation &transformation);

    bool operator ==(const Vertex &other);

private:
    Vec3 v;
    Vec3 n;
};


class Triangle
{
public:
    Triangle() = default;
    Triangle(const int32 &v1, const int32 &v2, const int32 &v3);

    int32 getV1() const;
    void setV1(const int32 &value);

    int32 getV2() const;
    void setV2(const int32 &value);

    int32 getV3() const;
    void setV3(const int32 &value);
private:
    array<int, 3> v;
};

class Material
{
public:
    Material() = default;
    Material(const Color &ka, const Color &kd, const Color &ks, float ns,
             float ni, float d);

    const Color &getKa();
    void setKa(const Color &value);

    const Color &getKd();
    void setKd(const Color &value);

    const Color &getKs();
    void setKs(const Color &value);

    float getNs() const;
    void setNs(float value);

    float getNi() const;
    void setNi(float value);

    float getD() const;
    void setD(float value);

private:
    Color ka;
    Color kd;
    Color ks;
    float ns;
    float ni;
    float d;
};


#endif // MESHDATA_H
