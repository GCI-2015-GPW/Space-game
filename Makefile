CXX = g++
CXXFLAGS = `sdl2-config --libs --cflags` -Wall -s -I. -lGL -lGLU
OBJ = main.o OpenGL.o

game: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)
