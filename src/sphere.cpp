#include<sphere.hpp>
#include<array>

// for testing
#include<iostream>


// contructor
Sphere::Sphere()
{

}

void Sphere::setPosition(Coord coord)
{
    this->pos.x = coord.x;
    this->pos.y = coord.y;
    this->pos.z = coord.z;
}

void Sphere::setPosition(float x, float y, float z)
{
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;
}

Coord Sphere::getPosition()
{
    return {this->pos.x, this->pos.y, this->pos.z};
}