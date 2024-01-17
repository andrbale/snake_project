CXX = g++
objects = src/snake.cpp src/game.cpp src/utils.cpp
libraries = -lraylib -lopengl32 -lgdi32 -lwinmm

all: main unit_tests

main: 
	$(CXX) -o Snake main.cpp $(objects) -I include/ -L lib/ $(libraries) 

unit_tests:
	$(CXX) -o unit_tests tests/unit_tests.cpp $(objects) -I include/ -L lib/ $(libraries) 

clean:
	rm *.o main