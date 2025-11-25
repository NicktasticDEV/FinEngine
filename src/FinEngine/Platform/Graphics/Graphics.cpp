#include "Graphics.h"
#include "GX/Graphics_GX.h"

namespace FinEngine {

    Graphics* Graphics::Create() {
        #ifdef FINENGINE_PLATFORM_WII
            return new Graphics_GX();
        #else
            return nullptr;
        #endif
    }

}