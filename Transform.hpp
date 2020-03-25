#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#pragma once
#include "Vector3.hpp"

class Transform
{
public:
    Vector3 position;
    float rotation;
    Vector3 scale;

    Transform(Vector3 position = Vector3(0, 0, 0),
              float rotation = 0, 
              Vector3 scale = Vector3(1, 1, 1));
};

#endif