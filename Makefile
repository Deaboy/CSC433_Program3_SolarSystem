CXX=g++
CXXLIBS=-lGL -lglut -lGLU
CXXFLAGS=-std=c++11 -Wall -g
EXECS=solarsystem

all: $(EXECS)

solarsystem: Main.o Planet.o SolarSystem.o GlutManager.o DrawingManager.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(CXXLIBS)

%.o: %.c
	$(CXX) $(CXXFLAGS) $@ -c $<

clean:
	$(RM) $(EXECS) *.o
