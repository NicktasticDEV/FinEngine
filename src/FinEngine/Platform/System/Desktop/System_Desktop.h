#pragma once
#include "../System.h"
#include <GLFW/glfw3.h>

namespace FinEngine {

    class System_Desktop : public System {
        public:
            static GLFWwindow* window;

            void Init() override;
            void Update() override;
            void Shutdown() override;
    };

}