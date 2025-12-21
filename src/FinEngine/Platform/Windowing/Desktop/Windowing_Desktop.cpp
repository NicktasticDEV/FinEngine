#include "Windowing_Desktop.h"
#include "FinEngine/Log.h"

namespace FinEngine {

    void Windowing_Desktop::Init() {
        glfwInit();
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
        }

        glfwMakeContextCurrent(window);
    }

    void Windowing_Desktop::Shutdown() {
        
    }

    void Windowing_Desktop::Update() {
        //glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}