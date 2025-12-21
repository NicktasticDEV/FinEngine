#include "FinEngine/Core/FinGame.h"

#include "FinEngine/Log.h"

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <chrono>
#include <thread>

namespace FinEngine {
    FinGame* FinGame::s_instance = nullptr;


    FinGame::FinGame(FinState *initialState) : nextState(initialState) {

        // Set instance
        LOG_INFO("FinGame", "Initializing");

        if (!s_instance) {
            s_instance = this;
        }

        Initialize();
        GameLoop();
        ShutDown();
    }


    void FinGame::SwitchState(FinState* state) {
        LOG_INFO("FinGame", "Switch state function called");
        nextState = state;
    }
    
    void FinGame::Exit() {
        LOG_INFO("FinGame", "Exit function called");
        isRunning = false;
    }


    void FinGame::Initialize() {
        system_.reset(System::Create());
        windowing_.reset(Windowing::Create());
        graphics_.reset(Graphics::Create());

        system_->Init();
        windowing_->Init();
        graphics_->Init();

        LOG_INFO("FinGame", "Game Initialized");
    }

    void FinGame::GameLoop() {
        while (isRunning) {

            // Begin rendering for this frame
            graphics_->BeginFrame();

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

            // Finish rendering and present the frame
            graphics_->EndFrame();

            // Handle windowing / platform-specific buffer swaps
            windowing_->Update();
        }
    }

    void FinGame::ShutDown() {
        LOG_INFO("FinGame", "Shutting down");
        if (currentState) {
            currentState->destroy();
            delete currentState;
            currentState = nullptr;
        }

        graphics_->Shutdown();
        windowing_->Shutdown();
        system_->Shutdown();
        LOG_INFO("FinGame", "Shutdown complete");
    }


    FinGame::~FinGame() {
        LOG_INFO("FinGame", "Game Terminated");
        if (s_instance == this) {
            s_instance = nullptr;
        }
    }
}