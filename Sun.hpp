#ifndef _SUN_HPP_
#define _SUN_HPP_

#pragma once
#include "Object.hpp"
#include <cmath>

class Sun : public Object
{
public:
    Sun(float radius = 1, Vector3 topColor = Vector3(0, 0, 0), Vector3 botColor = Vector3(0, 0, 0));
    void drawObject() override;
    void update(float deltaTime) override;
private:
    float radius;
    Vector3 topColor;
    Vector3 botColor;
};

#endif