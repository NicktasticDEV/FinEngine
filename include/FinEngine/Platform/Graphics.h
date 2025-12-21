#pragma once

namespace FinEngine {

    class Graphics {
        public:
            virtual ~Graphics() = default;

            virtual void Init();
            virtual void Shutdown();
            
            virtual void BeginFrame();
            virtual void EndFrame();
            
            virtual void ClearScreen(float r, float g, float b, float a );

            static Graphics* Create();
    };

}