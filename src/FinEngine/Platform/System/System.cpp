#include "System.h"
#include "Wii/System_Wii.h"

namespace FinEngine {

    System* System::Create() {
        #ifdef FINENGINE_PLATFORM_WII
            return new System_Wii();
        #else
            return nullptr;
        #endif
    }

}