#include "FinEngine/Graphics.h"

#include <GLFW/glfw3.h>
#include <stdio.h>

namespace FinEngine {

    void GFX_Init() {
        printf("FinGFX: Initializing Graphics System\n");

        if (!glfwInit()) {
            fprintf(stderr, "FinGFX: Failed to initialize GLFW\n");
            return;
        }

        GLFWwindow* window = glfwCreateWindow(800, 600, "FinEngine Window", nullptr, nullptr);
        if (!window) {
            fprintf(stderr, "FinGFX: Failed to create GLFW window\n");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
    }

    void GFX_PollEvents() {
        glfwPollEvents();
    }

    void GFX_Shutdown() {
        printf("FinGFX: Shutting down Graphics System\n");
        glfwDestroyWindow(glfwGetCurrentContext());
        glfwTerminate();
    }

}