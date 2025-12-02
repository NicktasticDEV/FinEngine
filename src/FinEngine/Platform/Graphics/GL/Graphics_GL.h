#pragma once

#include "../Graphics.h"

namespace FinEngine {

    class Graphics_GL : public Graphics {
        public:
            void Init() override;
            void Shutdown() override;
            void TestDraw(float r, float g, float b) override;
            void DrawDone() override;

    };

}