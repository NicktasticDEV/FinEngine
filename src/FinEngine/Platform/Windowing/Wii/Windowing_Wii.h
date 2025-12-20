#pragma once

#include "../Windowing.h"
#include <gccore.h>

namespace FinEngine {

    class Windowing_Wii : public Windowing {
        public:
            void Init() override;
            void Shutdown() override;
            void Update() override;

            static GXRModeObj* rmode;
            static void* xfb[2];
            static int currentXfb;

    };

}