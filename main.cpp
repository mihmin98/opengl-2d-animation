#include <iostream>
#include <vector>
#include "Object.hpp"
#include "ObjectManager.hpp"
#include "Polygon.hpp"
#include "Sun.hpp"
#include "Bird.hpp"

const int windowWidth = 800;
const int windowHeight = 800;
unsigned long previousTime;
unsigned long currentTime;

void init()
{
    // Create objects
    ObjectManager *objManager = ObjectManager::getInstance();
    Object *bird = new Bird();
    bird->transform = Transform(Vector3(400, 400));
    objManager->addObject(bird);

    // Get start time
    currentTime = previousTime = glutGet(GLUT_ELAPSED_TIME);

    // glut stuff
    glClearColor(1, 1, 1, 0); // Backgorund color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    ObjectManager::getInstance()->draw();
    glutSwapBuffers();
    glFlush();
}

void loop()
{
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - previousTime) / 1000.0;
    ObjectManager::getInstance()->update(deltaTime);
    previousTime = currentTime;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("pasari");

    init();
    glutDisplayFunc(draw);
    glutIdleFunc(loop);
    glutMainLoop();
}