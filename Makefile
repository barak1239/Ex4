CXX = g++
CXXFLAGS = -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system

all: tree tests

tree: main.o gui.o
	$(CXX) -o tree main.o gui.o $(CXXFLAGS)

tests: tests.o gui.o
	$(CXX) -o tests tests.o gui.o $(CXXFLAGS)

main.o: main.cpp node.hpp tree.hpp complex.hpp gui.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

gui.o: gui.cpp gui.hpp node.hpp tree.hpp complex.hpp
	$(CXX) $(CXXFLAGS) -c gui.cpp

tests.o: tests.cpp node.hpp tree.hpp complex.hpp gui.hpp doctest.h
	$(CXX) $(CXXFLAGS) -c tests.cpp

clean:
	rm -f *.o tree tests
