#include<iostream>
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<renderer.hpp>
#include<shader.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLFWwindow* startGLFW();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int loadJPG(const char *jpeg_path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float fov = 45.0f;

int main()
{
    GLFWwindow *window = startGLFW();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    initRenderer();
    // create shader
    Shader ourShader("shaders/3.3.shader.vs", "shaders/3.3.shader.fs");

    // Texture Rendering
    // -------------------------------------------------------------------------------
    // create both texture vartiables
    unsigned int texture1, texture2;
    texture1 = loadJPG("resources/textures/car.jpg");
    texture2 = loadJPG("resources/textures/gigachad.jpg");
    
    // added texture to our shader (ourShader)
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);



    // render loop
    while(!glfwWindowShouldClose(window ))
    {
        // checks for input each frame
        processInput(window);

        // set the background colour (RGBA)
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        // activate shader
        ourShader.use();

        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
        
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        ourShader.setMat4("projection", projection);

        // draw square
        drawSquare(texture1);

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

unsigned int loadJPG(const char *jpeg_path)
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