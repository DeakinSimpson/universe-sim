#pragma once

#include<sphere.hpp>

// initialise the renderer variables
void initRenderer();
void cleanRenderer();

// draw 3d objects
void drawObject(const std::vector<float> &verticies, const std::vector<unsigned int> &indicies, Shader* shader, glm::mat4 model);
void drawObjectNew(const std::vector<float> &verticies, const std::vector<unsigned int> &indicies, Shader* shader, glm::mat4 model);