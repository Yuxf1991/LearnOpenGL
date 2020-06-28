//
// Created by Yuxf1991 on 2019/12/22.
//

#include <iostream>

#include <utils/utils.h>

const char *WINDOW_NAME = "Hello Window!";

int main()
{
    std::cout << WINDOW_NAME << std::endl;
    GLFWwindow *window = initWindow(WINDOW_NAME);

    if (!window) {
        exit(EXIT_FAILURE);
    }

    if (initGLAD() == -1) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}