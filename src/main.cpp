#include<iostream>
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<renderer.hpp>
#include<shader.hpp>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <camera.hpp>
#include <viewWindow.hpp>
#include <sphere.hpp>

GLFWwindow* startGLFW();
void beginFrame();
void updateDeltaTime();
void endFrame(GLFWwindow *window);

ViewWindow* viewWindow = nullptr;

int main()
{
    GLFWwindow *window = ViewWindow::startGLFW();
    viewWindow = new ViewWindow("shaders/solid.shader.vs", "shaders/solid.shader.fs");
    initRenderer();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // set camera settings
    glm::mat4 projection = glm::perspective(glm::radians(viewWindow->camera.Zoom), (float)viewWindow->SCR_WIDTH / (float)viewWindow->SCR_HEIGHT, 0.1f, 100.0f);
    viewWindow->ourShader.setMat4("projection", projection); 

    Sphere sphere = Sphere(1, 1, 2, 3);
    sphere.setShader("shaders/solid.shader.vs", "shaders/solid.shader.fs");
   
    // render loop
    while(!glfwWindowShouldClose(window ))
    {
        viewWindow->updateDeltaTime();

        beginFrame();

        // checks for input each frame
        viewWindow->processInput(window);
        
        // drawSphere(sphere);
        drawObject(sphere.getVerticies(), sphere.getIndicies(), sphere.getShader(), sphere.getModelMatrix());
        // --------------------------------------------------------------------------------------------------------------------------------------------

        endFrame(window);
    }

    // cleanup
    cleanRenderer();

    // if the window closes terminate glfw
    glfwTerminate();
    return 0;
}

// render background as black
void beginFrame()
{
    // set the background colour (RGBA)
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void endFrame(GLFWwindow *window)
{
    // swaps colour buffers
    glfwSwapBuffers(window);

    // checks if any events are triggered
    glfwPollEvents();
}