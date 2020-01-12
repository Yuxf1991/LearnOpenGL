//
// Created by Yuxf1991 on 2019/12/22.
//

#ifndef LEARNOPENGL_UTILS_H
#define LEARNOPENGL_UTILS_H

// include顺序不能乱
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "config.h"

GLFWwindow *initWindow(const char *windowName);

int initGLAD();

int initCamera();

void framebufferSizeCallback(GLFWwindow *window, int width, int height);

void mouseCallback(GLFWwindow *window, double xPos, double yPos);

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);

void processInput(GLFWwindow *window, float deltaTime = 0.0f);

float getViewZoom();

glm::mat4 getViewMatrix();

#endif  // LEARNOPENGL_UTILS_H
