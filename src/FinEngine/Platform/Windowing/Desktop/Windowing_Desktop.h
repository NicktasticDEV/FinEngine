#pragma once
#include "FinEngine/Platform/Windowing.h"
#include <GLFW/glfw3.h>

namespace FinEngine {

    class Windowing_Desktop : public Windowing {
        public:
            void Init() override;
            void Shutdown() override;
            void Update() override;

            GLFWwindow* window = nullptr;
    };

}