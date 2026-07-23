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

GLFWwindow* startGLFW();

ViewWindow* viewWindow = nullptr;

int main()
{
    GLFWwindow *window = ViewWindow::startGLFW();
    viewWindow = new ViewWindow("shaders/3.3.shader.vs", "shaders/3.3.shader.fs");
    initRenderer();

    // Texture Rendering
    // -------------------------------------------------------------------------------
    // create both texture vartiables
    unsigned int texture1, texture2;
    texture1 = viewWindow->loadJPG("resources/textures/car.jpg");
    texture2 = viewWindow->loadJPG("resources/textures/gigachad.jpg");
    
    // added texture to our shader (ourShader)
    viewWindow->ourShader.use();
    viewWindow->ourShader.setInt("texture1", 0);
    viewWindow->ourShader.setInt("texture2", 1);

    // set camera settings
    glm::mat4 projection = glm::perspective(glm::radians(viewWindow->camera.Zoom), (float)viewWindow->SCR_WIDTH / (float)viewWindow->SCR_HEIGHT, 0.1f, 100.0f);
    viewWindow->ourShader.setMat4("projection", projection); 

    // render loop
    while(!glfwWindowShouldClose(window ))
    {
        // per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        viewWindow->deltaTime = currentFrame - viewWindow->lastFrame;
        viewWindow->lastFrame = currentFrame;

        // checks for input each frame
        viewWindow->processInput(window);

        // set the background colour (RGBA)
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        // activate shader
        viewWindow->ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(viewWindow->camera.Zoom), (float)viewWindow->SCR_WIDTH / (float)viewWindow->SCR_HEIGHT, 0.1f, 100.0f);
        viewWindow->ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = viewWindow->camera.GetViewMatrix();
        viewWindow->ourShader.setMat4("view", view);

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