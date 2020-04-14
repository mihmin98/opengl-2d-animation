#include "Bird.hpp"
#include <iostream>

Bird::Bird(Transform transform, int renderLayer) : Object(transform, renderLayer)
{
    velocity = Vector3(0, 0);

    state = 0;

    // Idle state
    stateDuration[0] = 3;
    GetIdleTime();
    wingStateAngle[0][0] = 5;
    wingStateAngle[0][1] = -10;

    // Wings down
    stateDuration[1] = 0.3;
    wingStateAngle[1][0] = -10;
    wingStateAngle[1][1] = -25;

    // Wings flexed
    stateDuration[2] = 0.3;
    wingStateAngle[2][0] = 35;
    wingStateAngle[2][1] = -30;

    // Wings up
    stateDuration[3] = 0.3;
    wingStateAngle[3][0] = 20;
    wingStateAngle[3][1] = 15;

    // Return to Idle
    stateDuration[4] = 0.3;
    wingStateAngle[4][0] = 5;
    wingStateAngle[4][1] = -10;

    // Calculate the wing speed
    for (int i = 1; i < 5; i++)
    {
        wingStateSpeed[i][0] = (wingStateAngle[i][0] - wingStateAngle[i - 1][0]) / stateDuration[i];
        wingStateSpeed[i][1] = (wingStateAngle[i][1] - wingStateAngle[i - 1][1]) / stateDuration[i];
    }

    bodySize = Vector3(25, 40);
    wingLength = 150;
    wingWidth = 22.5;
    wingRadius = 9;
    wingAngle[0] = wingStateAngle[0][0];
    wingAngle[1] = wingStateAngle[0][1];
    wingPosition[0] = Vector3(0, 0);
    wingPosition[1] = Vector3(wingPosition[0].x + wingLength * cos(wingAngle[0]) * DEG2RAD,
                              wingPosition[0].y + wingLength * sin(wingAngle[1]) * DEG2RAD);
}

void Bird::drawObject()
{
    glEnable(GL_POLYGON_SMOOTH);
    glColor3f(0, 0, 0);

    // Body
    // TODO: See if I can remove this matrix push and pop
    glPushMatrix();
    DrawEllipse(Vector3(0, 0), bodySize);
    glPopMatrix();

    // Right Wing 0
    glPushMatrix();
    glTranslatef(wingPosition[0].x, wingPosition[0].y, wingPosition[0].z);
    glRotatef(wingAngle[0], 0, 0, 1);
    DrawRoundLine(Vector3(0, 0), Vector3(wingLength, 0), wingWidth, wingRadius);
    glPopMatrix();

    // Right Wing 1
    glPushMatrix();
    glTranslatef(wingPosition[1].x, wingPosition[1].y, wingPosition[1].z);
    glRotatef(wingAngle[1], 0, 0, 1);
    DrawRoundLine(Vector3(0, 0), Vector3(wingLength, 0), wingWidth, wingRadius);
    glPopMatrix();

    // TODO: See if I can scale the right wing to flip it and get the left wing, like a mirror

    // Left Wing 0
    glPushMatrix();
    glTranslatef(-wingPosition[0].x, wingPosition[0].y, wingPosition[0].z);
    glRotatef(180 - wingAngle[0], 0, 0, 1);
    DrawRoundLine(Vector3(0, 0), Vector3(wingLength, 0), wingWidth, wingRadius);
    glPopMatrix();

    // Left Wing 1
    glPushMatrix();
    glTranslatef(-wingPosition[1].x, wingPosition[1].y, wingPosition[1].z);
    glRotatef(180 - wingAngle[1], 0, 0, 1);
    DrawRoundLine(Vector3(0, 0), Vector3(wingLength, 0), wingWidth, wingRadius);
    glPopMatrix();

    glDisable(GL_POLYGON_SMOOTH);
}

void Bird::update(float deltaTime)
{
    // Idle state
    if (state == 0)
    {
        idleTime -= deltaTime;
        if (idleTime <= 0)
        {
            state = 1;
            GetIdleTime();
        }
    }
    // Flapping state
    else
    {
        // Get the wing angle movment direction
        float wingDirection[2];
        wingDirection[0] = wingStateSpeed[state][0] >= 0 ? 1 : -1;
        wingDirection[1] = wingStateSpeed[state][1] >= 0 ? 1 : -1;

        wingAngle[0] += wingStateSpeed[state][0] * deltaTime;
        wingAngle[1] += wingStateSpeed[state][1] * deltaTime;

        if (wingDirection[0] * wingAngle[0] >= wingStateAngle[state][0] * wingDirection[0] ||
            wingDirection[1] * wingAngle[1] >= wingStateAngle[state][1] * wingDirection[1])
        {
            state = (state + 1) % 5;
        }
    }

    wingPosition[1] = Vector3(wingPosition[0].x + (wingLength - wingRadius) * cos(wingAngle[0] * DEG2RAD),
                              wingPosition[0].y + (wingLength - wingRadius) * sin(wingAngle[0] * DEG2RAD));

    // TODO: Maybe add rotation when the bird moves left or right

    // TODO: Maybe add velocity updates and stuff like that
}

void Bird::DrawEllipse(Vector3 origin, Vector3 radius)
{
    float rad;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        rad = i * DEG2RAD;
        glVertex2f(origin.x + cos(rad) * radius.x, origin.y + sin(rad) * radius.y);
    }
    glEnd();
}

void Bird::DrawRoundLine(Vector3 p1, Vector3 p2, float width, float radius)
{
    Vector3 left = p1, right = p2;
    if (p1.x > p2.x)
        std::swap(left, right);

    // Draw the 2 rectangles
    glBegin(GL_QUADS);

    // Horizontal rect
    glVertex2f(left.x, left.y - width / 2 + radius);   // Bottom Left
    glVertex2f(right.x, right.y - width / 2 + radius); // Bottom Right
    glVertex2f(right.x, right.y + width / 2 - radius); // Top Right
    glVertex2f(left.x, left.y + width / 2 - radius);   // Top Left

    // Vertical rect
    glVertex2f(left.x + radius, left.y - width / 2);   // Bottom Left
    glVertex2f(right.x - radius, right.y - width / 2); // Bottom Right
    glVertex2f(right.x - radius, right.y + width / 2); // Top Right
    glVertex2f(left.x + radius, left.y + width / 2);   // Top Left
    glEnd();

    // Draw the rounded corners
    float rad;
    Vector3 orig;

    // Bottom left
    orig = Vector3(left.x + radius, left.y - (width / 2 - radius));
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(orig.x, orig.y);
    for (int angle = 180; angle <= 270; angle++)
    {
        rad = angle * DEG2RAD;
        glVertex2f(orig.x + cos(rad) * radius, orig.y + sin(rad) * radius);
    }
    glEnd();

    // Bottom Right
    orig = Vector3(right.x - radius, right.y - (width / 2 - radius));
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(orig.x, orig.y);
    for (int angle = 270; angle <= 360; angle++)
    {
        rad = angle * DEG2RAD;
        glVertex2f(orig.x + cos(rad) * radius, orig.y + sin(rad) * radius);
    }
    glEnd();

    // Top Right
    orig = Vector3(right.x - radius, right.y + (width / 2 - radius));
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(orig.x, orig.y);
    for (int angle = 0; angle <= 90; angle++)
    {
        rad = angle * DEG2RAD;
        glVertex2f(orig.x + cos(rad) * radius, orig.y + sin(rad) * radius);
    }
    glEnd();

    // Top Left
    orig = Vector3(left.x + radius, left.y + (width / 2 - radius));
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(orig.x, orig.y);
    for (int angle = 90; angle <= 180; angle++)
    {
        rad = angle * DEG2RAD;
        glVertex2f(orig.x + cos(rad) * radius, orig.y + sin(rad) * radius);
    }
    glEnd();
}

void Bird::GetIdleTime()
{
    //srand(time(NULL) * transform.position.x * transform.position.y);
    srand(time(NULL) ^ reinterpret_cast<intptr_t>(this));
    int randomValue = rand();

    // Map the value from [0, RAND_MAX] to [0, stateDuration[0]]
    idleTime = randomValue * stateDuration[0] / RAND_MAX;
}

Vector3 Bird::getVelocity()
{
    return velocity;
}

void Bird::setVelocity(Vector3 velocity)
{
    this->velocity = velocity;
}