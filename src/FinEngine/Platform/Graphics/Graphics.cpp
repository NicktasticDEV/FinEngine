#include "Graphics.h"

#if defined(FINENGINE_PLATFORM_WII)
    #include "GX/Graphics_GX.h"
#elif defined(FINENGINE_PLATFORM_DESKTOP)
    #include "GL/Graphics_GL.h"
#endif

namespace FinEngine {

    void Graphics::Init() {}
    void Graphics::Shutdown() {}
    void Graphics::TestDraw(float r, float g, float b) {}
    void Graphics::DrawDone() {}

    Graphics* Graphics::Create() {
        #if  defined(FINENGINE_PLATFORM_WII)
            return new Graphics_GX();
        #elif defined(FINENGINE_PLATFORM_DESKTOP)
            return new Graphics_GL();
        #else
            return nullptr;
        #endif
    }

}