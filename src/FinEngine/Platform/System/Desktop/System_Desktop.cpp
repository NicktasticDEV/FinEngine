#include "System_Desktop.h"
#include "FinEngine/Log.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

namespace FinEngine {

    GLFWwindow* System_Desktop::window = nullptr;

    static constexpr double targetFrameTimeMs = 1000.0 / 60.0; // Targeting 60 FPS
    static auto lastFrameTime = std::chrono::steady_clock::now();

    void System_Desktop::Init() {
        LOG_INFO("System", "Initializing for Desktop Platform");

        if (!glfwInit()) {
            LOG_ERROR("System", "Error initializing windowing")
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
        }

        glfwMakeContextCurrent(window);

        LOG_INFO("System", "System successfully initialized");
    }

    void System_Desktop::Update() {
        glfwPollEvents();
    }

    void System_Desktop::Shutdown() {
        glfwTerminate();
        LOG_INFO("System", "Shutting down");
    }

}