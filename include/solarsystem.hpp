#pragma once

#include<planet.hpp>
#include<vector>

class SolarSystem
{
public:

    // constructor
    SolarSystem();

    // setters
    void addPlanet(Planet planet);

    // getters
    std::vector<Planet> getPlanets();


    // to move to private
    float getGravitationalForce(int planet1_index, int planet2_index);


private:
    std::vector<Planet> planets;

    // functions
};