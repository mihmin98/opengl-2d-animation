#include "Object.hpp"

Object::Object(Transform transform, int renderLayer)
{
    this->transform = transform;
    this->renderLayer = renderLayer;
}

void Object::draw()
{
    glPushMatrix();
    // Translate object to its current position
    glTranslatef(this->transform.position.x,
                 this->transform.position.y,
                 this->transform.position.z);

    // Rotate object
    if (this->transform.rotation != 0)
        glRotatef(this->transform.rotation, 0, 0, 1);

    // Scale object
    if (this->transform.scale != Vector3(1, 1, 1))
        glScalef(this->transform.scale.x,
                 this->transform.scale.y,
                 this->transform.scale.z);

    this->drawObject();
    glPopMatrix();
}