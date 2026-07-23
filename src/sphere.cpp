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

Coord Sphere::getPosition()
{
    return {this->pos.x, this->pos.y, this->pos.z};
}