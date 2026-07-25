#pragma once

#include<vector>
#include<shader.hpp>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    void setShader(const char* vertex_shader, const char* fragment_shader);

    // getters
    Coord getPos() const;
    float getRadius() const;
    Shader* getShader() const;
    std::vector<float> getVerticies() const;
    std::vector<unsigned int> getIndicies() const;
    glm::mat4 getModelMatrix();

    // functions
    void draw();

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