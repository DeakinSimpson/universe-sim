#include<iostream>
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>

GLFWwindow* startGLFW();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// create the vertex shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// create fragment shader
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main()
{
    GLFWwindow *window = startGLFW();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // set the verticies for the triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    // create the vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // set the vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);




    // while the window should be open
    while(!glfwWindowShouldClose(window ))
    {
        // checks for input each frame
        processInput(window);

        // set the background colour (RGBA)
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw triangle --------------------------------------------



        // create the vertex buffer object (VBO)
        unsigned int VBO;
        glGenBuffers(1, &VBO);

        // bind the buffer to be current buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // set the buffer data to be the verticies
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // swaps colour buffers
        glfwSwapBuffers(window);

        // checks if any events are triggered
        glfwPollEvents();
    }

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