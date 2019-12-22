//
// Created by Yuxf1991 on 2019/12/22.
//

#include <iostream>

#include "utils.h"

GLFWwindow *initWindow(const char *windowName) {
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW." << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window =
        glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowName, nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    return window;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}