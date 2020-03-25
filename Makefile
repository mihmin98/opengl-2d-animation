CC=g++
CFLAGS=-Wall
LIBS=-lglut -lGL -lGLU

Vector3: Vector3.cpp Vector3.hpp
	$(CC) -c Vector3.cpp -o Vector3.o $(LIBS) $(CFLAGS)

Transform: Transform.cpp Transform.hpp
	$(CC) -c Transform.cpp -o Transform.o $(LIBS) $(CFLAGS)

clean:
	rm Vector3.o Transform.o