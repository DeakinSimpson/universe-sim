#include<iostream>
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<renderer.hpp>
#include<shader.hpp>

GLFWwindow* startGLFW();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int createShaderProgram();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    GLFWwindow *window = startGLFW();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    initRenderer();
    // create shader
    Shader ourShader("shaders/3.3.shader.vs", "shaders/3.3.shader.fs");

    // render loop
    while(!glfwWindowShouldClose(window ))
    {
        // checks for input each frame
        processInput(window);

        // set the background colour (RGBA)
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw square
        ourShader.use();
        drawSquare();

        // swaps colour buffers
        glfwSwapBuffers(window);

        // checks if any events are triggered
        glfwPollEvents();
    }

    // cleanup
    cleanRenderer();

    // if the window closes terminate glfw
    glfwTerminate();
    return 0;
}

// initialise glfw
GLFWwindow* startGLFW()
{
    // initialise glfw
    if (!glfwInit())
    {
        std::cout << "Failed to start GLFW" << std::endl;
        return nullptr;
    }

    // create a window
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Universe Sim", NULL, NULL);

    // check if its initialised correctly
    if (window == nullptr)
    {
        std::cout << "window failed to initialise" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    // make the current window the context
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to Initialise GLAD" << std::endl;
        return nullptr;
    }

    // set the default viewpoer size
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    return window;
}

// processes the input keys for the window
void processInput(GLFWwindow *window)
{
    // if the escape key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        // set the window state to close
        glfwSetWindowShouldClose(window, true);
    }

}

// allow resizing with the viewport
void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}
