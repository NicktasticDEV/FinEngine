#pragma once

namespace FinEngine {

    class Graphics {
        public:
            virtual ~Graphics() = default;

            virtual void Init();
            virtual void Shutdown();
            
            virtual void BeginFrame();
            virtual void EndFrame();
            virtual void ClearScreen();

            static Graphics* Create();
    };

}