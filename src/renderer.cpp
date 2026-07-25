#include "renderer.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <viewwindow.hpp>

extern ViewWindow* viewWindow;

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

void drawTexturedSquare(unsigned int texture) {
    // set the verticies for the triangle
    float vertices[] = {
        // positions          // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    // set the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set the edge buffer array (indicies)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // set for 3.3.shader...
    // ----------------------------------------------------------------------------------------------------
    // set position (location 0) shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // set texcoord (location 1) shader
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // clear the buffer array by setting 0
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // draw the elements in the buffers
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // clear the vertex buffer
    glBindVertexArray(0);
}

void drawSolidSquare() {
    // set the verticies for the triangle
    float vertices[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    glBindVertexArray(VAO);

    // set the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set the edge buffer array (indicies)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // clear the buffer array by setting 0
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // draw the elements in the buffers
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // clear the vertex buffer
    glBindVertexArray(0);    
}

void drawSphere(const Sphere &sphere)
{
    // shading
    // -------------------------------------------------------------
    Shader* shader = sphere.getShader();
    shader->use();

    // get the projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(viewWindow->camera.Zoom), (float)viewWindow->SCR_WIDTH / (float)viewWindow->SCR_HEIGHT, 0.1f, 100.0f);
    // set the "projection" variable in the shader to projection matrix
    shader->setMat4("projection", projection);

    // get the viewport matrix
    glm::mat4 view = viewWindow->camera.GetViewMatrix();
    // set the "view" variable in the shader to view matrix
    shader->setMat4("view", view);

    // translate the model based on the cameras position
    Coord pos = sphere.getPos();
    // translate the spheres verticie postitions
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));
    // set model variable in shader to model matrix
    shader->setMat4("model", model);

    // set the shader colour "objectColor" to white
    shader->setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));

    // rendering
    //--------------------------------------------------------------
    const std::vector<float> &verticies = sphere.getVerticies();
    const std::vector<unsigned int> &indicies = sphere.getIndicies();

    glBindVertexArray(VAO);

    // set the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), verticies.data(), GL_STATIC_DRAW);

    // set the edge buffer array (indicies)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), indicies.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // clear the buffer array by setting 0
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // draw the elements in the buffers
    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);

    // clear the vertex buffer
    glBindVertexArray(0);   
}

