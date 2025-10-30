#pragma once

namespace FinEngine {

    class Graphics {
        public:
            virtual ~Graphics() = default;

            virtual void Init() = 0;
            virtual void Shutdown() = 0;
            virtual void TestDraw() = 0;

            static Graphics* Create();
    };

}