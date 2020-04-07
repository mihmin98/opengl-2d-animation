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

    void draw();
    virtual void drawObject() = 0; // Pure virtual function that says how the object is drawn (ex. shapes, etc)
    virtual void update(float deltaTime) = 0;
};

#endif