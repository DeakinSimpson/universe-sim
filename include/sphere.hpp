#pragma once

#include<array>

struct Coord {
    float x;
    float y;
    float z;
};

class Sphere {
public:

    Sphere();

    void setPosition(Coord coord);
    Coord getPosition();

private:
    Coord pos;
};