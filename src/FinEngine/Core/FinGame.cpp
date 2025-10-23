#include "FinEngine/Core/FinGame.h"
#include "FinEngine/Log.h"

#include <stdio.h>
#include <stdlib.h>

namespace FinEngine {
    FinGame* FinGame::s_instance = nullptr;

    FinGame::FinGame(int gameWidth, int gameHeight, FinState *initialState) : initialGameWidth(gameWidth), initialGameHeight(gameHeight), nextState(initialState) {
        // Set instance
        if (!s_instance) {
            s_instance = this;
        }

        LOG_INFO("FinGame", "Game Initialized (Width: " + std::to_string(initialGameWidth) + ", Height: " + std::to_string(initialGameHeight) + ")");

        // State update
        while (isRunning) {

            // State init
            if (nextState)
            {
                LOG_INFO("FinGame", "Switching State");
                if (currentState)
                {
                    currentState->cleanup();
                    delete currentState;
                }

                currentState = nextState;
                nextState = nullptr;

                if (currentState)
                {
                    currentState->init();
                    LOG_INFO("FinGame", "State Initialized");
                }
            }

            currentState->update();
            currentState->render();
        }

        // Exit
        if (currentState) {
            currentState->cleanup();
            delete currentState;
            currentState = nullptr;
        }
    }

    void FinGame::SwitchState(FinState* state) {
        LOG_INFO("FinGame", "Switch state function called");
        nextState = state;
    }
    
    void FinGame::Exit() {
        LOG_INFO("FinGame", "Exit function called");
        isRunning = false;
    }

    FinGame::~FinGame() {
        LOG_INFO("FinGame", "Game Terminated");
        if (s_instance == this) {
            s_instance = nullptr;
        }
    }
}