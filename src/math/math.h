#ifndef MATH_H
#define MATH_H


class Math
{
public:
    static float Gauss2(float sigma, int x, int y);

    template<class T>
    static T Clamp(const T &value, const T &max, const T &min);
};

template<class T>
T Math::Clamp(const T &value, const T &min, const T &max)
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}


#endif // MATH_H
