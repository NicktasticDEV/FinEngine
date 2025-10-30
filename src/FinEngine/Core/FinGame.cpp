#include "FinEngine/Core/FinGame.h"

#include "FinEngine/Log.h"
#include "FinEngine/Platform/System/System.h"
#include "FinEngine/Platform/Graphics/Graphics.h"
#include "FinEngine/Platform/Audio/Audio.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory>

namespace FinEngine {
    FinGame* FinGame::s_instance = nullptr;

    FinGame::FinGame(int gameWidth, int gameHeight, FinState *initialState) : initialGameWidth(gameWidth), initialGameHeight(gameHeight), nextState(initialState) {
        // Set instance
        LOG_INFO("FinGame", "Initializing");

        if (!s_instance) {
            s_instance = this;
        }

        // Create and initialize systems owned by this game instance
        system_.reset(System::Create());
        graphics_.reset(Graphics::Create());
        audio_.reset(Audio::Create());

        system_->Init();
        graphics_->Init();
        audio_->Init();

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

        // Shutdown systems
        audio_->Shutdown();
        graphics_->Shutdown();
        system_->Shutdown();
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