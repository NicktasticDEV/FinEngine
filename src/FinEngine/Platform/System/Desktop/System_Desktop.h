#pragma once
#include "FinEngine/Platform/System.h"
#include <GLFW/glfw3.h>

namespace FinEngine {

    class System_Desktop : public System {
        public:
            void Init() override;
            void Shutdown() override;
    };

}