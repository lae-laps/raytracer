CC = g++
CFLAGS = -g -Wall
TARGET = main
BUILDDIR = build/

all: main.o collection.o io.o render.o vec3.o ray.o
	$(CC) $(CFLAGS) -o $(TARGET) $(BUILDDIR)main.o $(BUILDDIR)collection.o $(BUILDDIR)io.o $(BUILDDIR)render.o $(BUILDDIR)vec3.o $(BUILDDIR)ray.o

main.o:
	$(CC) $(CFLAGS) -c main.cpp -o $(BUILDDIR)main.o

io.o:
	$(CC) $(CFLAGS) -c io/io.cpp -o $(BUILDDIR)io.o

render.o:
	$(CC) $(CFLAGS) -c render/render.cpp -o $(BUILDDIR)render.o

vec3.o:
	$(CC) $(CFLAGS) -c vec3/vec3.cpp -o $(BUILDDIR)vec3.o

ray.o:
	$(CC) $(CFLAGS) -c ray/ray.cpp -o $(BUILDDIR)ray.o

collection.o:
	$(CC) $(CFLAGS) -c objects/collection/collection.cpp -o $(BUILDDIR)collection.o

clean:
	$(RM) $(BUILDDIR)*.o $(TARGET)

