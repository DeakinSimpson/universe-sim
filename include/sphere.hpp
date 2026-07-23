#pragma once

#include<vector>
#include<shader.hpp>

// Coord struct, used as an easy way to get the position without using fixed sized arrays with indexing to get value
struct Coord {
    float x;
    float y;
    float z;
};

class Sphere {
public:
    Sphere(float radius, Coord coord);
    Sphere(float radius, float x, float y, float z);

    // setters
    void setPos(Coord coord);
    void setPos(float x, float y, float z);
    void setRadius(float radius);

    // getters
    Coord getPos();
    float getRadius();

    void setShader(const char* vertex_shader, const char* fragment_shader);

private:
    // variables
    float x;
    float y;
    float z;
    float radius;
    std::vector<float> verticies;
    std::vector<unsigned int> indicies;
    Shader* shader;

    // functions
    void setVerticies();
    void setIndicies();
};