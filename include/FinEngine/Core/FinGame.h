#pragma once
#include "FinState.h"

#include "FinEngine/FinEngineAPI.h"
#include <memory>

namespace FinEngine {

    class System;
    class Windowing;
    class Graphics;

    class FINENGINE_API FinGame {
        public:
            FinGame(FinState* initialState);
            ~FinGame();

            //void Run();

            static FinGame& instance() { return *s_instance; }
            static FinGame* instancePtr() { return s_instance; }

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

            // Owned systems (single instances per game)
            std::unique_ptr<System> system_;
            std::unique_ptr<Windowing> windowing_;
            std::unique_ptr<Graphics> graphics_;
    };

}
