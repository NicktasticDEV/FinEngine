#pragma once
#include "FinState.h"
#include "FinEngine/FinEngineAPI.h"

namespace FinEngine {

    class FINENGINE_API FinGame {
        public:
            FinGame(int gameWidth, int gameHeight, FinState *initialState);
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
    };

}
