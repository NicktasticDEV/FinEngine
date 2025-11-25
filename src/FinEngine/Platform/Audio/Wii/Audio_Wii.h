#pragma once
#include "../Audio.h"

namespace FinEngine {

    class Audio_Wii : public Audio {
        public:
            void Init() override;
            void Shutdown() override;
            void TestSound() override;

    };

}