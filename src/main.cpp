#include<iostream>
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<renderer.hpp>
#include<shader.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<camera.hpp>
#include<sphere.hpp>
#include<engine.hpp>
#include<planet.hpp>

void beginFrame();
void endFrame(GLFWwindow *window);

Camera* Camera::instance = nullptr;
Engine *engine = nullptr;

int main()
{
    engine = new Engine();
    engine->init();

    Planet earth = Planet(1, 1, 0, 3, 1, 1, 1);
    earth.setShader("shaders/planet.vs", "shaders/planet.fs");

    Planet sun = Planet(2, 4, 0, 3, 1, 1, 1);
    sun.setShader("shaders/sun.vs", "shaders/sun.fs");

   
    // render loop
    while(!glfwWindowShouldClose(engine->window))
    {
        engine->updateDeltaTime();
        beginFrame();

        // checks for input each frame
        engine->camera.processInput(engine->window, engine->deltaTime);
        
        // drawSphere(sphere);
        sun.draw(glm::vec3(sun.getPos().x, sun.getPos().y, sun.getPos().z));
        earth.draw(glm::vec3(sun.getPos().x, sun.getPos().y, sun.getPos().z));

        earth.addPos(0.01, 0, 0);

        endFrame(engine->window);
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