#include "Graphics_GL.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "FinEngine/Log.h"
#include "FinEngine/Platform/System/Desktop/System_Desktop.h"

namespace FinEngine {

    void Graphics_GL::Init() {
        LOG_INFO("Graphics", "Initializing with OpenGL backend");

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        } 
        
        LOG_INFO("Graphics", "Graphics successfully initialized");
    }

    void Graphics_GL::Shutdown() {
        LOG_INFO("Graphics", "Shutting down");
    }

    void Graphics_GL::BeginFrame() {

    }

    void Graphics_GL::EndFrame() {
        
    }

    void Graphics_GL::ClearScreen() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

}