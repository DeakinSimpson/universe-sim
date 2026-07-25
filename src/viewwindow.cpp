#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<viewwindow.hpp>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

// static members need this one-time out-of-class definition
ViewWindow* ViewWindow::instance = nullptr;

ViewWindow::ViewWindow(const char* vertex_shader_path, const char* fragment_shader_path) : 
    SCR_WIDTH(screen_width),
    SCR_HEIGHT(screen_height),
    camera(glm::vec3(0.0f, 0.0f, 3.0f)),
    ourShader(vertex_shader_path, fragment_shader_path)
{
    instance = this; // remember this object so the static callbacks can find it

    lastX = SCR_WIDTH / 2.0f;
    lastY = SCR_HEIGHT / 2.0f;
    firstMouse = true;

    // timing
    deltaTime = 0.0f;	// time between current frame and last frame
    lastFrame = 0.0f;
}

// initialise glfw
GLFWwindow* ViewWindow::startGLFW()
{
    // initialise glfw
    if (!glfwInit())
    {
        std::cout << "Failed to start GLFW" << std::endl;
        return nullptr;
    }

    // create a window
    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, "Universe Sim", NULL, NULL);

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
    glViewport(0, 0, screen_width, screen_height);

    // set callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    return window;
}

// processes the input keys for the window
void ViewWindow::processInput(GLFWwindow *window)
{
    // if the escape key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        // set the window state to close
        glfwSetWindowShouldClose(window, true);
    }

    // when clicking wasd move the camera 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    // toggle wireframe
    // check if E is pressed
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        // if pressed and pressed wireframe, then change to fill
        if (!ePressedLastFrame)
        {
            wireframe = !wireframe;
            glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
        }
        ePressedLastFrame = true;
    }
    else
    {
        // if pressed and not pressed last frame process
        ePressedLastFrame = false;
    }

}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void ViewWindow::mouse_callback(GLFWwindow*, double xposIn, double yposIn)
{
    // get the current xpos
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (instance->firstMouse)
    {
        // set the last x and y pos to the current
        instance->lastX = xpos;
        instance->lastY = ypos;
        instance->firstMouse = false;
    }

    // set the offset between the mouse movements to the difference between the current and the last frame
    float xoffset = xpos - instance->lastX;
    float yoffset = instance->lastY - ypos;

    // set the x andy pos
    instance->lastX = xpos;
    instance->lastY = ypos;

    // proccess the mouse movement with the offsets
    instance->camera.ProcessMouseMovement(xoffset, yoffset);
}

void ViewWindow::scroll_callback(GLFWwindow*, double, double yoffset)
{
    // if scrolling change the fov
    instance->camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// allow resizing with the viewport
void ViewWindow::framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    // set the viewports width and height to the windows width and height
    glViewport(0, 0, width, height);
}

unsigned int ViewWindow::loadJPG(const char *jpeg_path)
{
    unsigned int output_texture;

    glGenTextures(1, &output_texture);
    glBindTexture(GL_TEXTURE_2D, output_texture); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(jpeg_path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return output_texture;
}

void ViewWindow::updateDeltaTime()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}