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
    void setPosition(float x, float y, float z);
    
    Coord getPosition();

private:
    Coord pos;
};