#pragma once

#include "FinEngine/Platform/Graphics/Graphics.h"
#include "FinEngine/FinEngineAPI.h"

namespace FinEngine {

    class FINENGINE_API Renderer2D
    {
        public:
            static void Init(Graphics* backend);
            static void Shutdown();
        private:
            static Graphics* s_Backend;
    };

} // namespace FinEngine