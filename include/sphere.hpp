#pragma once

#include<array>

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
    Coord pos;
};