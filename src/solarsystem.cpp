#include<solarsystem.hpp>
#include<vector>
#include<glm/glm.hpp>
#include<math.h>

float G = 6.67430 * pow(10, -11);

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

#include<iostream>

// private functions
// ----------------------------------------------------------------------------------------------
float SolarSystem::getForce(int planet1_index, int planet2_index)
{
    Planet *planet1 = &this->planets[planet1_index];
    Planet *planet2 = &this->planets[planet2_index];

    float m1 = planet1->getMass();
    float m2 = planet2->getMass();

    glm::vec3 planet1_pos = glm::vec3(planet1->getPos().x, planet1->getPos().y, planet1->getPos().z);
    glm::vec3 planet2_pos = glm::vec3(planet2->getPos().x, planet2->getPos().y, planet2->getPos().z);

    float r = glm::distance(planet1_pos, planet2_pos);

    float F = G * ((m1 * m2) / (pow(r, 2)));

    std::cout << "m1: " << m1 << ", m2: " << m2 << ", r2: " << r << ", F: " << F << std::endl;

    return 0.0f;
}

