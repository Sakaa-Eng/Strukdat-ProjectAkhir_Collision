CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
INCLUDE = -Iinclude
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = src/main.cpp src/Bola.cpp
OUT = bola

all:
	$(CXX) $(CXXFLAGS) $(SRC) $(INCLUDE) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)
