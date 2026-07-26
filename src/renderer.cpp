#include "renderer.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <engine.hpp>

extern Engine* engine;

static unsigned int VAO; // holds setup info (including VBO & EBO)
static unsigned int VBO; // holds vertex positions
static unsigned int EBO; // holds indicies

void initRenderer() {
    // generate 1 ID and store it in the position &name 
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO); // bind VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // make VBO the active buffer

    /*
    0 — which attribute to configure (matches layout (location = 0) in your vertex shader)
    3 — each vertex has 3 values (x, y, z)
    GL_FLOAT — those values are floats
    GL_FALSE — don't normalise the values
    3 * sizeof(float) — the stride, how many bytes to jump to get to the next vertex
    (void*)0 — offset of where the data starts in the buffer (0 = start from the beginning)    
    */
    // position (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texcoord (location 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbinds VAO by binding 0
    glBindVertexArray(0);    
}

void cleanRenderer() {
    // delete the arrays stored in VAO, VBO, EBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


glm::vec3 initialColour = glm::vec3(1.0f, 1.0f, 1.0f);

void drawObject(const std::vector<float> &verticies, const std::vector<unsigned int> &indicies, Shader* shader, glm::mat4 model, glm::vec3 lightPos)
{
    // activate the shader
    shader->use();

    // get the projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(engine->camera.Zoom), (float)engine->SCR_WIDTH / (float)engine->SCR_HEIGHT, 0.1f, 100.0f);
    // set the "projection" variable in the shader to projection matrix
    shader->setMat4("projection", projection);

    // get the viewport matrix
    glm::mat4 view = engine->camera.GetViewMatrix();
    // set the "view" variable in the shader to view matrix
    shader->setMat4("view", view);

    // set model variable in shader to model matrix
    shader->setMat4("model", model);

    // set the shader colour "objectColor" to white
    shader->setVec3("objectColor", initialColour);

    // set the lightColor
    shader->setVec3("lightColor", glm::vec3(1.0f, 0.85f, 0.61f));

    // set up a light
    shader->setVec3("lightPos", lightPos);

    glBindVertexArray(VAO);

    // set the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), verticies.data(), GL_STATIC_DRAW);

    // set the edge buffer array (indicies)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), indicies.data(), GL_STATIC_DRAW);

    /*
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    0 = location 0 in the shader
    3 = the number of components (x,y,z)
    GL_FLOAT = the component type (floats)
    GL_FALSE = dont normalise
    6 * sizeof(float) = the stride (how many bytes each chunck has, x,y,z,u,v)
    (void*)0 = the offset (start at byte 0 in each chunk)
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // clear the buffer array by setting 0
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // draw the elements in the buffers
    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);

    // clear the vertex buffer
    glBindVertexArray(0);   
}