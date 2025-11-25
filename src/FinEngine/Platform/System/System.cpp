#include "System.h"

#if defined(FINENGINE_PLATFORM_WII)
#include "Wii/System_Wii.h"
#endif

namespace FinEngine {

    System* System::Create() {
        #ifdef FINENGINE_PLATFORM_WII
            return new System_Wii();
        #else
            return nullptr;
        #endif
    }

}