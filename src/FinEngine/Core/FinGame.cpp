#include "FinEngine.h"
#include <stdio.h>
#include <stdlib.h>

#include "FinEngine/Graphics.h"

namespace FinEngine {
    FinGame* FinGame::s_instance = nullptr;

    FinGame::FinGame(int gameWidth, int gameHeight, FinState *initialState) : initialGameWidth(gameWidth), initialGameHeight(gameHeight), nextState(initialState) {
        // Set instance
        if (!s_instance) {
            s_instance = this;
        }

        printf("FinGame: Game Initialized (Width: %d, Height: %d)\n", initialGameWidth, initialGameHeight);

        // Initialize Systems
        GFX_Init();

        // State update
        while (isRunning) {

            GFX_PollEvents();

            // State init
            if (nextState)
            {
                printf("FinGame: Switching State\n");

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
                    printf("FinGame: State Initialized\n");
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
        GFX_Shutdown();
    }

    void FinGame::SwitchState(FinState* state) {
        printf("FinGame: Switch state function called\n");
        nextState = state;
    }
    
    void FinGame::Exit() {
        printf("FinGame: Exit function called\n");
        isRunning = false;
    }

    FinGame::~FinGame() {
        printf("FinGame: Game Terminated\n");
        if (s_instance == this) {
            s_instance = nullptr;
        }
    }
}