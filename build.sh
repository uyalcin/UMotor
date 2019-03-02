g++ -g -c main.cpp Entity.cpp Vector3.cpp World.cpp Plane.cpp Plane.h header.h Cube.cpp Matrix.cpp Matrix.h Matrix4.h Matrix4.cpp Vector4.cpp Vector4.h Triangle.h Triangle.cpp Primitive.h Object.cpp Object.h -std=c++11
g++ main.o Entity.o Plane.o Vector3.o World.o Cube.o Matrix.o Matrix4.o Vector4.o Triangle.o Object.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

