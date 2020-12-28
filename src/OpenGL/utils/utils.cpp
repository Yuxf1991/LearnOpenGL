//
// Created by Yuxf1991 on 2019/12/22.
//

#include <memory>
#include <iostream>

#include "utils.h"
#include "Camera.h"

glm::vec3 gCameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
bool gFirstMouse = true;
float gLastX = START_X;
float gLastY = START_Y;
std::unique_ptr<Camera> gCamera;

GLFWwindow *initWindow(const char *windowName)
{
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW." << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowName, nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    return window;
}

int initCamera()
{
    gCamera = std::make_unique<Camera>(gCameraPosition);
    if (gCamera == nullptr) {
        std::cout << "Failed to create camera: no memory!" << std::endl;
        return -1;
    }
    return 0;
}

int initGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow *window, double xPos, double yPos)
{
    if (gFirstMouse) {
        gLastX = static_cast<float>(xPos);
        gLastY = static_cast<float>(yPos);
        gFirstMouse = false;
    }

    float xOffset = static_cast<float>(xPos) - gLastX;
    float yOffset = gLastY - static_cast<float>(yPos);  // reversed since y-coordinates go from bottom to top

    gLastX = static_cast<float>(xPos);
    gLastY = static_cast<float>(yPos);

    if (gCamera != nullptr) {
        gCamera->processMouseMovement(xOffset, yOffset);
    }
}

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
    if (gCamera != nullptr) {
        gCamera->processMouseScroll(static_cast<float>(yOffset));
    }
}

void processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (gCamera != nullptr) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            gCamera->processKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            gCamera->processKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            gCamera->processKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            gCamera->processKeyboard(RIGHT, deltaTime);
    }
}

float getViewZoom()
{
    if (gCamera != nullptr) {
        return gCamera->getZoom();
    }
    return ZOOM;
}

glm::mat4 getViewMatrix()
{
    if (gCamera != nullptr) {
        return gCamera->getViewMatrix();
    }
    return glm::mat4(1.0f);
}
