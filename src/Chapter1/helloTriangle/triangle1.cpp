//
// Created by Yuxf1991 on 2019/12/22.
//

#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils/utils.h"
#include "utils/Shader.h"

const char *WINDOW_NAME = "Hello Triangle!";
const char *vertexPath = "resources/shaders/chapter1/triangle1.vs";
const char *fragmentPath = "resources/shaders/chapter1/triangle1.fs";

float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

int main()
{
    std::cout << WINDOW_NAME << std::endl;

    GLFWwindow *window = initWindow(WINDOW_NAME);
    if (!window) {
        exit(EXIT_FAILURE);
    }

    if (initCamera() == -1) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (initGLAD() == -1) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);

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
    if (!ourShader) {
        std::cout << "Failed to create shader: no memory!" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (ourShader->compile() == -1) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // timing
    float deltaTime = 0.0f;  // time between current frame and last frame
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, deltaTime);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader->use();
        glm::mat4 projection =
            glm::perspective(glm::radians(getViewZoom()), WINDOW_WIDTH * 1.0f / WINDOW_HEIGHT, 0.1f, 100.0f);
        ourShader->setMat4f("projection", projection);
        ourShader->setMat4f("view", getViewMatrix());
        glm::mat4 model = glm::mat4(1.0f);
        ourShader->setMat4f("model", model);

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