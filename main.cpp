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
Object *player;

void init()
{
    // Create objects
    ObjectManager *objManager = ObjectManager::getInstance();
    Transform t = Transform(Vector3(200, 600), 0, Vector3(0.33, 0.33));
    objManager->addObject(new Bird(t, 5));
    t = Transform(Vector3(300, 500), 0, Vector3(0.33, 0.33));
    objManager->addObject(new Bird(t, 5));
    t = Transform(Vector3(400, 650), 0, Vector3(0.33, 0.33));
    objManager->addObject(new Bird(t, 5));
    t = Transform(Vector3(500, 450), 0, Vector3(0.33, 0.33));
    objManager->addObject(new Bird(t, 5));
    t = Transform(Vector3(550, 550), 0, Vector3(0.33, 0.33));
    objManager->addObject(new Bird(t, 5));
    t = Transform(Vector3(350, 350), 0, Vector3(0.33, 0.33));
    objManager->addObject(new Bird(t, 5));

    t = Transform(Vector3(windowWidth / 2, windowHeight / 2), 0, Vector3(0.5, 0.5, 0.5));
    player = new Bird(t, 1);
    objManager->addObject(player);

    // Add background
    std::vector<Vector3> backgroundVertices{Vector3(0, 0), Vector3(windowWidth, 0),
                                            Vector3(windowWidth, windowHeight), Vector3(0, windowHeight)};
    std::vector<Vector3> backgroundColors{Vector3(0.65, 0.15, 0), Vector3(0.65, 0.15, 0),
                                          Vector3(0.9, 0.2, 0), Vector3(0.9, 0.2, 0)};

    Object *background = new Polygon(backgroundVertices, backgroundColors);
    background->renderLayer = 10;
    objManager->addObject(background);

    // Add sun
    Object *sun = new Sun(300, Vector3(1, 0.6, 0), Vector3(1, 0.3, 0));
    sun->transform.position = Vector3(windowWidth / 2, windowHeight / 3 * 2);
    sun->renderLayer = 9;
    objManager->addObject(sun);

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

void mouse(int x, int y)
{
    Vector3 previousPos = player->transform.position;
    ((Bird *)player)->setVelocity(Vector3(x - previousPos.x, (windowHeight - y) - previousPos.y));
    player->transform.position = Vector3(x, windowHeight - y);
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
    glutPassiveMotionFunc(mouse);
    glutMainLoop();
}