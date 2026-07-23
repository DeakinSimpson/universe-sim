#pragma once

#include<array>

// Coord struct, used as an easy way to get the position without using fixed sized arrays with indexing to get value
struct Coord {
    float x;
    float y;
    float z;
};

class Sphere {
public:
    Sphere(Coord coord);
    Sphere(float x, float y, float z);

    void setPos(Coord coord);
    void setPos(float x, float y, float z);

    Coord getPos();

private:
    float x;
    float y;
    float z;
};