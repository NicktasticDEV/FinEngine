#pragma once

#include "../Graphics.h"

namespace FinEngine {

    class Graphics_GL : public Graphics {
        public:
            void Init() override;
            void Shutdown() override;

            void BeginFrame() override;
            void EndFrame() override;

            void ClearScreen() override;
    };

}