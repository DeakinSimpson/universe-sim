#include<solarsystem.hpp>
#include<vector>

SolarSystem::SolarSystem()
{

}

// setters
// ----------------------------------------------------------------------------------------------

// add a planet to the planets vector
void SolarSystem::addPlanet(Planet planet)
{
    planets.push_back(planet);
}

// getters
// ----------------------------------------------------------------------------------------------

// get all planets
std::vector<Planet> SolarSystem::getPlanets()
{
    return this->planets;
}