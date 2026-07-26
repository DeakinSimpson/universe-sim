#pragma once

#include<camera.hpp>
#include<GLFW/glfw3.h>

class Engine
{
public:
    const unsigned int SCR_WIDTH;
    const unsigned int SCR_HEIGHT;

    // frame timing
    float deltaTime;
    float lastFrame;
    Camera camera;
    GLFWwindow *window;

    // constructor
    Engine();

    // engine initialiser
    void init();

    // functions
    unsigned int loadJPG(const char *jpeg_path);
    void updateDeltaTime();

private:
    static GLFWwindow* startGLFW();
    static void framebuffer_size_callback(GLFWwindow*, int width, int height);


};