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

}