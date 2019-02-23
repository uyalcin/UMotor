g++ -c main.cpp Entity.cpp Vector3.cpp World.cpp Plane.cpp Plane.h header.h Cube.cpp Matrix.cpp Matrix.h -std=c++11
g++ main.o Entity.o Plane.o Vector3.o World.o Cube.o Matrix.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

