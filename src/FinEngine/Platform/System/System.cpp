#include "System.h"

#if defined(FINENGINE_PLATFORM_WII)
    #include "Wii/System_Wii.h"
#elif defined(FINENGINE_PLATFORM_DESKTOP)
    #include "Desktop/System_Desktop.h"
#endif

namespace FinEngine {

    void System::Init() {}
    void System::Update() {}
    void System::Shutdown() {}

    System* System::Create() {
        #if defined(FINENGINE_PLATFORM_WII)
            return new System_Wii();
        #elif defined(FINENGINE_PLATFORM_DESKTOP)
            return new System_Desktop();
        #else
            return nullptr;
        #endif
    }

}