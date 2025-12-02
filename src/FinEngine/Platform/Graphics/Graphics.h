#pragma once

namespace FinEngine {

    class Graphics {
        public:
            virtual ~Graphics() = default;

            virtual void Init();
            virtual void Shutdown();
            virtual void TestDraw(float r, float g, float b);
            virtual void DrawDone();

            static Graphics* Create();
    };

}