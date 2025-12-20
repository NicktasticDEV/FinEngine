#pragma once
#include "../System.h"

#include <gccore.h>

namespace FinEngine {

    class System_Wii : public System {
        public:
            void Init() override;
            void Shutdown() override;
    };

}