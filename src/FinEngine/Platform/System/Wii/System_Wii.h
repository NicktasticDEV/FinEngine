#pragma once
#include "../System.h"

#include <gccore.h>

namespace FinEngine {

    class System_Wii : public System {
        public:
            static GXRModeObj *rmode;
            static void *xfb[2];
            static int currentXfb;

            void Init() override;
            void Shutdown() override;

    };

}