#pragma once
#include "FinState.h"
#include "FinEngine/FinEngineAPI.h"
#include <memory>

namespace FinEngine {

    // Forward declarations for core systems
    class System;
    class Graphics;
    class Audio;

    class FINENGINE_API FinGame {
        public:
            FinGame(int gameWidth, int gameHeight, FinState* initialState);
            ~FinGame();

            const int initialGameWidth;
            const int initialGameHeight;

            static FinGame& instance() { return *s_instance; }
            static FinGame* instancePtr() { return s_instance; }

            // Functions
            void SwitchState(FinState* state);
            void Exit();

        private:
            static FinGame* s_instance;

            FinState* currentState = nullptr;
            FinState* nextState = nullptr;

            bool isRunning = true;

            // Owned systems (single instances per game)
            std::unique_ptr<System> system_;
            std::unique_ptr<Graphics> graphics_;
            std::unique_ptr<Audio> audio_;
    };

}
