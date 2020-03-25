#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#pragma once
#include "Transform.hpp"
#include "GL/freeglut.h"

class Object
{
public:
    Transform transform;
    int renderLayer; // Lower layer for elements in background

    Object(Transform transform = Transform(), int renderLayer = 0);

    void drawObject(); // When redefining function in child, always push and pop matrix
};

#endif