#pragma once

#include "../Graphics.h"

namespace FinEngine {

    class Graphics_GX : public Graphics {
        public:
            void Init() override;
            void Shutdown() override;
            void TestDraw() override;

    };

}