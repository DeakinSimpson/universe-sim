#include<planet.hpp>

// initialise planet variables
Planet::Planet(float radius, float x, float y, float z, float mass, float velocity, float direction) : Sphere(radius, x, y, z)
{
    this->mass = mass;
    this->velocity = velocity;
    this->direction = direction;
}


// getters
// ---------------------------------------------------------------------------------------------------
float Planet::getMass()
{
    return this->mass;
}

float Planet::getVelocity()
{
    return this->velocity;
}

float Planet::getDirection()
{
    return this->direction;
}

// setters
// ---------------------------------------------------------------------------------------------------
void Planet::setMass(float mass)
{
    this->mass = mass;
}

void Planet::setVelocity(float velocity)
{
    this->velocity = velocity;
}

void Planet::setDirection(float direction)
{
    this->direction = direction;
}