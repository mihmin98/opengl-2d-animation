#ifndef _BIRD_HPP_
#define _BIRD_HPP_

#pragma once
#include "Object.hpp"
#include <cstdlib>
#include <ctime>
#include <cfloat>
#include <cmath>
#include <algorithm>

class Bird : public Object
{
public:
    Bird(Transform transform = Transform(), int renderLayer = 0);

    void drawObject() override;
    void update(float deltaTime) override;
    void DrawEllipse(Vector3 origin, Vector3 radius);
    void DrawRoundLine(Vector3 p1, Vector3 p2, float width, float radius);
    void GetIdleTime(); // Sets idleTime to a random value between o and stateDuration[0]

    Vector3 getVelocity();
    void setVelocity(Vector3 velocity);

protected:
    Vector3 velocity;       // Object velocity
    int state;              // Animation state
    float stateDuration[5]; // Time in seconds of each state; Time for idle state is chosen from the interval [0, stateDuration[0]]
    float idleTime;
    float wingStateAngle[5][2]; // Angles for the wings in each state
    float wingStateSpeed[5][2];
    Vector3 bodySize; // Ellipse size
    float wingLength;
    float wingWidth;
    float wingRadius;
    Vector3 wingPosition[2]; // Position of the wing segments
    float wingAngle[2];      // Wing segments angle
    float rotationSpeed;
    float maxRotation;
};

#endif