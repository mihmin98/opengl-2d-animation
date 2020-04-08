CC=g++
CFLAGS=-Wall
LIBS=-lglut -lGL -lGLU

all: Vector3 Transform Object ObjectManager Polygon Sun Bird

Vector3: Vector3.cpp Vector3.hpp
	$(CC) -c Vector3.cpp -o Vector3.o $(LIBS) $(CFLAGS)

Transform: Transform.cpp Transform.hpp
	$(CC) -c Transform.cpp -o Transform.o $(LIBS) $(CFLAGS)

Object: Object.cpp Object.hpp
	$(CC) -c Object.cpp -o Object.o $(LIBS) $(CFLAGS)

ObjectManager: ObjectManager.cpp ObjectManager.hpp
	$(CC) -c ObjectManager.cpp -o ObjectManager.o $(LIBS) $(CFLAGS)

Polygon: Polygon.cpp Polygon.hpp
	$(CC) -c Polygon.cpp -o Polygon.o $(LIBS) $(CFLAGS)

Sun: Sun.cpp Sun.hpp
	$(CC) -c Sun.cpp -o Sun.o $(LIBS) $(CFLAGS)

Bird: Bird.cpp Bird.hpp
	$(CC) -c Bird.cpp -o Bird.o $(LIBS) $(CFLAGS)

clean:
	rm Vector3.o Transform.o Object.o ObjectManager.o Polygon.o Sun.o Bird.o