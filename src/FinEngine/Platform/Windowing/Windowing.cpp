#include "Windowing.h"

#if defined(FINENGINE_PLATFORM_WII)
    #include "Wii/Windowing_Wii.h"
#elif defined(FINENGINE_PLATFORM_DESKTOP)
    #include "Desktop/Windowing_Desktop.h"
#endif

namespace FinEngine {

    void Windowing::Init() {}
    void Windowing::Shutdown() {}
    void Windowing::Update() {}

    Windowing* Windowing::Create() {
        #if defined(FINENGINE_PLATFORM_WII)
            return new Windowing_Wii();
        #elif defined(FINENGINE_PLATFORM_DESKTOP)
            return new Windowing_Desktop();
        #else
            return nullptr;
        #endif
    }

}