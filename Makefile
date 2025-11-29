CXX=g++
CXXFLAGS=-std=c++17 -Wall -O2
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

SRC=src/main.cpp src/Bola.cpp
INC=-Iinclude

all:
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) -o bola $(LIBS)

clean:
	rm -f bola
