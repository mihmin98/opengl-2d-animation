#ifndef _POLYGON_HPP_
#define _POLYGON_HPP_

#pragma once
#include "Object.hpp"
#include <vector>

class Polygon : public Object
{
public:
    Polygon();
    Polygon(std::vector<Vector3> vertex, std::vector<Vector3> color);
    void drawObject() override;
    void update(float deltaTime) override;

private:
    std::vector<Vector3> vertex;
    std::vector<Vector3> color;
};

#endif