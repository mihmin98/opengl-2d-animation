#include "Polygon.hpp"

Polygon::Polygon()
{
    this->vertex = std::vector<Vector3>();
    this->color = std::vector<Vector3>();
}

Polygon::Polygon(std::vector<Vector3> vertex, std::vector<Vector3> color)
{
    this->vertex = vertex;
    this->color = color;
}

void Polygon::drawObject()
{
    glBegin(GL_POLYGON);
    for (unsigned long i = 0; i < vertex.size(); i++)
    {
        glColor3f(color[i].x, color[i].y, color[i].z);
        glVertex2f(vertex[i].x, vertex[i].y);
    }
    glEnd();
}

void Polygon::update(float deltaTime)
{
}
