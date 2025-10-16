#include "FinEngine/Graphics.h"

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace FinEngine {

    namespace {
        GLFWwindow* g_window = nullptr;
    }

    void GFX_Init() {
        printf("FinGFX: Initializing Graphics System\n");

        if (!glfwInit()) {
            fprintf(stderr, "FinGFX: Failed to initialize GLFW\n");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

        g_window = glfwCreateWindow(640, 480, "FinEngine Window", nullptr, nullptr);
        if (!g_window) {
            fprintf(stderr, "FinGFX: Failed to create GLFW window\n");
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(g_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            fprintf(stderr, "FinGFX: Failed to initialize GLAD\n");
            glfwDestroyWindow(g_window);
            g_window = nullptr;
            glfwTerminate();
            return;
        }

        glViewport(0, 0, 640, 480);
    }

    void GFX_PollEvents() {
        if (!g_window) {
            return;
        }

        // Draw code
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(g_window);
    }

    bool GFX_ShouldClose() {
        if (!g_window) {
            return true;
        }

        return glfwWindowShouldClose(g_window) == GLFW_TRUE;
    }

    void GFX_Shutdown() {
        printf("FinGFX: Shutting down Graphics System\n");

        if (g_window) {
            glfwDestroyWindow(g_window);
            g_window = nullptr;
        }

        glfwTerminate();
    }

}