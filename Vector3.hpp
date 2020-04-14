#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#pragma once
#include <string>

class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3(float x = 0, float y = 0, float z = 0);
    std::string ToString();

    static float DotProduct(const Vector3 &a, const Vector3 &b);
    static Vector3 CrossProduct(const Vector3 &a, const Vector3 &b);

    Vector3 &operator+=(const Vector3 &rhs);
    Vector3 &operator-=(const Vector3 &rhs);

    friend bool operator==(const Vector3 &a, const Vector3 &b);
    friend bool operator!=(const Vector3 &a, const Vector3 &b);
    friend Vector3 operator+(Vector3 lhs, const Vector3 &rhs);
    friend Vector3 operator-(Vector3 lhs, const Vector3 &rhs);
};

#endif