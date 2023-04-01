CC = g++
CFLAGS = -g -Wall
TARGET = main
BUILDDIR = build/

all: main.o collection.o io.o filewriter.o vec3.o ray.o sphere.o
	$(CC) $(CFLAGS) -o $(TARGET) $(BUILDDIR)main.o $(BUILDDIR)collection.o $(BUILDDIR)io.o $(BUILDDIR)vec3.o $(BUILDDIR)ray.o $(BUILDDIR)sphere.o $(BUILDDIR)filewriter.o

main.o:
	$(CC) $(CFLAGS) -c main.cpp -o $(BUILDDIR)main.o

io.o:
	$(CC) $(CFLAGS) -c io/io.cpp -o $(BUILDDIR)io.o

filewriter.o:
	$(CC) $(CFLAGS) -c filewriter/filewriter.cpp -o $(BUILDDIR)filewriter.o

vec3.o:
	$(CC) $(CFLAGS) -c vec3/vec3.cpp -o $(BUILDDIR)vec3.o

ray.o:
	$(CC) $(CFLAGS) -c ray/ray.cpp -o $(BUILDDIR)ray.o

collection.o:
	$(CC) $(CFLAGS) -c objects/collection/collection.cpp -o $(BUILDDIR)collection.o

sphere.o:
	$(CC) $(CFLAGS) -c objects/sphere/sphere.cpp -o $(BUILDDIR)sphere.o

clean:
	$(RM) $(BUILDDIR)*.o $(TARGET)

