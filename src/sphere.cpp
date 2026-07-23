#include<sphere.hpp>
#include<array>

// for testing
#include<iostream>


// contructors
// --------------------------------------------------------------------------

Sphere::Sphere(float radius, Coord coord)
{
    this->radius = radius;
    this->x = coord.x;
    this->y = coord.y;
    this->z = coord.z;
}

Sphere::Sphere(float radius, float x, float y, float z)
{
    this->radius = radius;
    this->x = x;
    this->y = y;
    this->z = z;
}

// setters
// --------------------------------------------------------------------------

// set pos with Coord struct
void Sphere::setPos(Coord coord)
{
    this->x = coord.x;
    this->y = coord.y;
    this->z = coord.z;
}

// set pos with x, y, z input
void Sphere::setPos(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// set the radius of the sphere
void Sphere::setRadius(float radius)
{
    this->radius = radius;
}

// getters
// --------------------------------------------------------------------------
Coord Sphere::getPos()
{
    return {this->x, this->y, this->z};
}

float Sphere::getRadius()
{
    return this->radius;
}