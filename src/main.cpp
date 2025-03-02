#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

GLfloat vertices[] = {
    //  Coordinates    /      Colors  //
    0.5f,  0.5f, 0.0f,   0.8f, 0.3f, 0.02f,
    0.5f, -0.5f, 0.0f,   1.0f, 0.6f, 0.02f,
   -0.5f, -0.5f, 0.0f,   0.4f, 0.45f, 0.7f,
   -0.5f,  0.5f, 0.0f,   0.6f, 0.2f, 0.45f
};

GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "window", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    Shader shaderProgram("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
    GLuint rotationLoc = glGetUniformLocation(shaderProgram.ID, "rotation4d");

    while (!glfwWindowShouldClose(window)){
        float angle = glfwGetTime();
        float cosTheta = cos(angle);
        float sinTheta = sin(angle);

        GLfloat rotation4d[] = {
            cosTheta, -sinTheta, 0, 0,
            sinTheta, cosTheta,  0, 0,
            0,       0,          1, 0,
            0,       0,          0, 1
        };


        // input
        processInput(window);

        //  rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shaderProgram.Activate();
        glUniform1f(uniID, 0.0f);
        glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, rotation4d);

        VAO1.Bind();

        // draw filled in triangles
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // check all events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}