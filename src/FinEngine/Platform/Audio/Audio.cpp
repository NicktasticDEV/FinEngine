#include "Audio.h"
#include "Wii/Audio_Wii.h"

namespace FinEngine {

    Audio* Audio::Create() {
        #ifdef FINENGINE_PLATFORM_WII
            return new Audio_Wii();
        #else
            return nullptr;
        #endif
    }

}
