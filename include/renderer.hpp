#pragma once

#include<sphere.hpp>

void initRenderer();
void cleanRenderer();
void drawTexturedSquare(unsigned int texture);
void drawSolidSquare();
void drawSphere(const Sphere &sphere);