#pragma once

#include<sphere.hpp>

// create a planet object that extends sphere
class Planet : public Sphere
{
public:
    // constructor
    Planet(float radius, float x, float y, float z, float mass, float velocity = 0.0f, float direction = 0.0f);

    // getters
    float getMass();
    float getVelocity();
    float getDirection();

    // setters
    void setMass(float mass);
    void setVelocity(float velocity);
    void setDirection(float direction);

private:
    float mass;
    float velocity;
    float direction;
};