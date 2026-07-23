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

    // set camera settings
    glm::mat4 projection = glm::perspective(glm::radians(viewWindow->camera.Zoom), (float)viewWindow->SCR_WIDTH / (float)viewWindow->SCR_HEIGHT, 0.1f, 100.0f);
    viewWindow->ourShader.setMat4("projection", projection); 

    Sphere sphere = Sphere(1, 1, 2, 3);
    // sphere.setPosition({1, 2, 3});
    std::cout << sphere.getPos().x << std::endl;

    // render loop
    while(!glfwWindowShouldClose(window ))
    {
        viewWindow->updateDeltaTime();

        beginFrame();

        // checks for input each frame
        viewWindow->processInput(window);
        
        // TO REMOVE AFTER drawSphere is implemented
        // --------------------------------------------------------------------------------------------------------------------------------------------
        // activate shader
        viewWindow->ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(viewWindow->camera.Zoom), (float)viewWindow->SCR_WIDTH / (float)viewWindow->SCR_HEIGHT, 0.1f, 100.0f);
        viewWindow->ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = viewWindow->camera.GetViewMatrix();
        viewWindow->ourShader.setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));

        // create transformations
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(viewWindow->ourShader.ID, "model");
        unsigned int viewLoc  = glGetUniformLocation(viewWindow->ourShader.ID, "view");
        
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        // draw square
        drawSolidSquare();
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