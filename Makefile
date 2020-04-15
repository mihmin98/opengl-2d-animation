CC=g++
CFLAGS=-Wall
LIBS=-lglut -lGL -lGLU

APPNAME=animation
OBJS=Vector3.o \
	 Transform.o \
	 Object.o \
	 ObjectManager.o \
	 Polygon.o \
	 Sun.o \
	 Bird.o \
	 main.o

all: $(APPNAME)

$(APPNAME): $(OBJS)
	$(CC) -o $(APPNAME) $(OBJS) $(LIBS) $(CFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm $(APPNAME) $(OBJS)
