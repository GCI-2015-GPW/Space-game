CXX = g++
CXXFLAGS = `sdl2-config --libs --cflags` -Wall -s
OBJ = main.o

game: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)
