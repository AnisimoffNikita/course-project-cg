#include "meshdata.h"

Vertex::Vertex(const Vec3 v, const Vec3 n)
    : v(v)
    , n(n)
{
}

const Vec3 &Vertex::getV() const
{
    return v;
}

void Vertex::setV(const Vec3 &value)
{
    v = value;
}

const Vec3 &Vertex::getN()
{
    return n;
}

void Vertex::setN(const Vec3 &value)
{
    n = value;
}

void Vertex::transform(const Transformation &transformation)
{
    n += v;
    transformation.transform(v);
    transformation.transform(n);
    n -= v;
}

bool Vertex::operator ==(const Vertex &other)
{
    return n == other.n && v == other.v;
}


Triangle::Triangle(const int32 &v1, const int32 &v2, const int32 &v3)
    : v{v1, v2, v3}
{
}

int32 Triangle::getV1() const
{
    return v[0];
}

void Triangle::setV1(const int32 &value)
{
    v[0] = value;
}

int32 Triangle::getV2() const
{
    return v[1];
}

void Triangle::setV2(const int32 &value)
{
    v[1] = value;
}

int32 Triangle::getV3() const
{
    return v[2];
}

void Triangle::setV3(const int32 &value)
{
    v[2] = value;
}

Material::Material(const Color &ka, const Color &kd, const Color &ks, float ns,
                   float ni, float d)
    : ka(ka)
    , kd(kd)
    , ks(ks)
    , ns(ns)
    , ni(ni)
    , d(d)
{
}

const Color &Material::getKa()
{
    return ka;
}

void Material::setKa(const Color &value)
{
    ka = value;
}

const Color &Material::getKd()
{
    return kd;
}

void Material::setKd(const Color &value)
{
    kd = value;
}

const Color &Material::getKs()
{
    return ks;
}

void Material::setKs(const Color &value)
{
    ks = value;
}

float Material::getD() const
{
    return d;
}

void Material::setD(float value)
{
    d = value;
}

float Material::getNi() const
{
    return ni;
}

void Material::setNi(float value)
{
    ni = value;
}

float Material::getNs() const
{
    return ns;
}

void Material::setNs(float value)
{
    ns = value;
}
