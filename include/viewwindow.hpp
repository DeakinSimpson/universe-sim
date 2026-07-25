#pragma once

#include<camera.hpp>
#include<glm/glm.hpp>
#include<shader.hpp>

// variables
const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

class ViewWindow
{
public:
    // settings
    const unsigned int SCR_WIDTH;
    const unsigned int SCR_HEIGHT;

    // camera
    Camera camera;
    float lastX;
    float lastY;
    bool firstMouse;

    // timing
    float deltaTime;
    float lastFrame;

    // shader variables
    Shader ourShader;

    // window constructer
    ViewWindow(const char* vertex_shader_path, const char* fragment_shader_path);

    // initialise glfw
    static GLFWwindow* startGLFW();

    // processes the input keys for the window
    void processInput(GLFWwindow *window);

    unsigned int loadJPG(const char *jpeg_path);

    // glfw: whenever the mouse moves, this callback is called
    // -------------------------------------------------------

    static void mouse_callback(GLFWwindow*, double xposIn, double yposIn);
    static void scroll_callback(GLFWwindow*, double, double yoffset);
    static void framebuffer_size_callback(GLFWwindow*, int width, int height);

    void updateDeltaTime();

private:
    // points at "the current" ViewWindow object, so the static callbacks
    // above (which have no `this` of their own) can still reach camera/
    // lastX/etc. Set once, inside the constructor.
    static ViewWindow* instance;
};