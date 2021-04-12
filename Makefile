CXX = g++
CXXFLAGS = -std=c++0x -Wall

OBJECTS = Main.o WinRen.o Entity.o Snake.o Apple.o

LINKER_FLAGS = -lSDL2 -lSDL2_image

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LINKER_FLAGS) -o $@ $^

$(OBJECTS): WinRen.hpp Entity.hpp

