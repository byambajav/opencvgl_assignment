CXX=g++
CXXFLAGS=-Wall -O3 -fopenmp `pkg-config opencv --cflags`
LDLIBS=-lglut -lGL -lGLU -fopenmp `pkg-config opencv --libs`

main: main.o rendering.o detection.o drawing.o menu.o lighting.o playsound.o sphere.o

clean:
	rm *.o main
