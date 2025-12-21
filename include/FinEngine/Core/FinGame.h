#pragma once
#include "FinState.h"

#include "FinEngine/Platform/System.h"
#include "FinEngine/Platform/Windowing.h"
#include "FinEngine/Platform/Graphics.h"

#include "FinEngine/FinEngineAPI.h"
#include <memory>

namespace FinEngine {

    class FINENGINE_API FinGame {
        public:
            FinGame(FinState* initialState);
            ~FinGame();

            //void Run();

            static FinGame& instance() { return *s_instance; }
            static FinGame* instancePtr() { return s_instance; }

            // Accessors for systems
            System& GetSystem() { return *system_; }
            Windowing& GetWindowing() { return *windowing_; }
            Graphics& GetGraphics() { return *graphics_; }

            // Functions
            void SwitchState(FinState* state);
            void Exit();

        private:
            static FinGame* s_instance;

            FinState* currentState = nullptr;
            FinState* nextState = nullptr;

            void Initialize();
            void GameLoop();
            void ShutDown();

            bool isRunning = true;

            std::unique_ptr<System> system_;
            std::unique_ptr<Windowing> windowing_;
            std::unique_ptr<Graphics> graphics_;
    };

}
