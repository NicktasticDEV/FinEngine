#include "FinEngine/Core/FinGame.h"

#include "FinEngine/Log.h"
#include "FinEngine/Platform/System/System.h"
#include "FinEngine/Platform/Graphics/Graphics.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <cmath>
#include <chrono>
#include <thread>

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

        system_->Init();
        graphics_->Init();

        LOG_INFO("FinGame", "Game Initialized (Width: " + std::to_string(initialGameWidth) + ", Height: " + std::to_string(initialGameHeight) + ")");

        // State update
        while (isRunning) {
            system_->Update();

            // State init
            if (nextState)
            {
                LOG_INFO("FinGame", "Next state requested");

                if (currentState)
                {
                    LOG_INFO("FinGame", "Destroying current state");
                    currentState->destroy();
                    delete currentState;
                    currentState = nullptr;
                }

                LOG_INFO("FinGame", "Switching to next state");
                currentState = nextState;
                nextState = nullptr;

                if (currentState)
                {
                    LOG_INFO("FinGame", "Creating next state");
                    currentState->create();
                }
                else
                {
                    LOG_INFO("FinGame", "No next state to switch to, exiting game loop");
                }


                LOG_INFO("FinGame", "Next state switch complete");
            };

            currentState->update();
            currentState->draw();
            graphics_->DrawDone();
        }

        // Exit
        LOG_INFO("FinGame", "Shutting down");
        if (currentState) {
            currentState->destroy();
            delete currentState;
            currentState = nullptr;
        }

        graphics_->Shutdown();
        system_->Shutdown();
        LOG_INFO("FinGame", "Shutdown complete");
        exit(0);
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