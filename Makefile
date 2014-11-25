CXX=g++
CXXLIBS=-lGL -lglut -lGLU
CXXFLAGS=-std=c++11 -Wall -g
EXECS=solarsystem

all: $(EXECS)

solarsystem: Main.o DrawingManager.o GlutManager.o SolarSystem.o Planet.o\
Star.o Ring.o Camera.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(CXXLIBS)

%.o: %.c
	$(CXX) $(CXXFLAGS) $@ -c $<

clean:
	$(RM) $(EXECS) *.o *~
