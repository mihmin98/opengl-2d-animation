#ifndef _OBJECT_MANAGER_HPP_
#define _OBJECT_MANAGER_HPP_

#pragma once
#include "Object.hpp"
#include <vector>

class ObjectManager
{
public:
    static ObjectManager *getInstance();
    void addObject(Object *obj);
    void update(float deltaTime);
    void draw();

private:
    ObjectManager();
    static ObjectManager *instance;
    std::vector<Object *> objects;
};

#endif