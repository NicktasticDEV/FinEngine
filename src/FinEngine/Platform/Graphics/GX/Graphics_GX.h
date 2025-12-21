#pragma once

#include "FinEngine/Platform/Graphics.h"

namespace FinEngine {

    class Graphics_GX : public Graphics {
        public:
            void Init() override;
            void Shutdown() override;

            void BeginFrame() override;
            void EndFrame() override;
            
            void ClearScreen(float r, float g, float b, float a) override;
    };

}