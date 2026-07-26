#include<engine.hpp>
#include<GLAD/glad.h>
#include<glm/glm.hpp>
#include<iostream>
#include<camera.hpp>
#include<renderer.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// TODO: change how these are being declared
int screen_width = 800;
int screen_height = 600;

Engine::Engine() : 
    SCR_WIDTH(screen_width),
    SCR_HEIGHT(screen_height),
    camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
    // timing
    deltaTime = 0.0f;	// time between current frame and last frame
    lastFrame = 0.0f;
}

void Engine::init()
{
    // start GLFW
    this->window = startGLFW();

    // initialise the renderer
    initRenderer();
}

// public functions
// ---------------------------------------------------------------------------------------
unsigned int Engine::loadJPG(const char *jpeg_path)
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

// private functions
// ---------------------------------------------------------------------------------------

// allow resizing with the viewport
void Engine::framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    // set the viewports width and height to the windows width and height
    glViewport(0, 0, width, height);
}

// initialise glfw
GLFWwindow* Engine::startGLFW()
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
    glfwSetCursorPosCallback(window, Camera::mouse_callback);
    glfwSetScrollCallback(window, Camera::scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    return window;
}

void Engine::updateDeltaTime()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
