#include "Sun.hpp"

Sun::Sun(float radius, Vector3 topColor, Vector3 botColor)
{
    this->radius = radius;
    this->topColor = topColor;
    this->botColor = botColor;
}

void Sun::drawObject()
{
    // We make the circle by drawing quads to get the gradient effect
    float rad;
    glBegin(GL_QUADS);
    for (int i = 1; i < 180; i++)
    {
        // Top Left
        rad = i * DEG2RAD;
        glColor3f(topColor.x, topColor.y, topColor.z);
        glVertex2f(radius * cos(rad), radius * sin(rad));

        // Bottom Left
        rad = (360 - i) * DEG2RAD;
        glColor3f(botColor.x, botColor.y, botColor.z);
        glVertex2f(radius * cos(rad), radius * sin(rad));

        // Bottom Right
        rad = (360 - (i - 1)) * DEG2RAD;
        glColor3f(botColor.x, botColor.y, botColor.z);
        glVertex2f(radius * cos(rad), radius * sin(rad));

        // Top Right
        rad = (i - 1) * DEG2RAD;
        glColor3f(topColor.x, topColor.y, topColor.z);
        glVertex2f(radius * cos(rad), radius * sin(rad));
    }
    glEnd();
}

void Sun::update(float deltaTime)
{
}