CC = g++
CFLAGS = -g -Wall
TARGET = main
BUILDDIR = build/

all: main.o io.o render.o vec3.o ray.o point.o color.o
	$(CC) $(CFLAGS) -o $(TARGET) $(BUILDDIR)*

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

point.o:
	$(CC) $(CFLAGS) -c point/point.cpp -o $(BUILDDIR)point.o

color.o:
	$(CC) $(CFLAGS) -c color/color.cpp -o $(BUILDDIR)color.o

clean:
	$(RM) $(BUILDDIR)*.o $(TARGET)

