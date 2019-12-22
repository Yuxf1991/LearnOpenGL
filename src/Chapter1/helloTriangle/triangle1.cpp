//
// Created by Yuxf1991 on 2019/12/22.
//

#include <iostream>
#include <memory>

#include "utils/utils.h"
#include "utils/Shader.h"

const char *WINDOW_NAME = "Hello Triangle!";
const char *vertexPath = "resources/shaders/Chapter1/triangle1.vs";
const char *fragmentPath = "resources/shaders/Chapter1/triangle1.fs";

float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

int main() {
    std::cout << WINDOW_NAME << std::endl;

    GLFWwindow *window = initWindow(WINDOW_NAME);
    if (!window) {
        exit(EXIT_FAILURE);
    }

    if (!initGLAD()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::unique_ptr<Shader> ourShader = std::make_unique<Shader>(vertexPath, fragmentPath);
    if (ourShader->compile() == -1) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader->use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}