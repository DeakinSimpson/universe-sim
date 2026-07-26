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

private:
    std::vector<Planet> planets;

};