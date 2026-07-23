#include<sphere.hpp>
#include<array>

// for testing
#include<iostream>


// contructors
// --------------------------------------------------------------------------

Sphere::Sphere(Coord coord)
{
    this->pos.x = coord.x;
    this->pos.y = coord.y;
    this->pos.z = coord.z;
}

Sphere::Sphere(float x, float y, float z)
{
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;
}

// setters
// --------------------------------------------------------------------------

// set pos with Coord struct
void Sphere::setPos(Coord coord)
{
    this->pos.x = coord.x;
    this->pos.y = coord.y;
    this->pos.z = coord.z;
}

// set pos with x, y, z input
void Sphere::setPos(float x, float y, float z)
{
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;
}

// getters
// --------------------------------------------------------------------------
Coord Sphere::getPos()
{
    return {this->pos.x, this->pos.y, this->pos.z};
}