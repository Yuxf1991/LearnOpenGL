//
// Created by Yuxf1991 on 2019/12/22.
//

#ifndef LEARNOPENGL_UTILS_H
#define LEARNOPENGL_UTILS_H

// include顺序不能乱
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "config.h"

GLFWwindow *initWindow(const char *windowName);

void framebufferSizeCallback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

#endif // LEARNOPENGL_UTILS_H
