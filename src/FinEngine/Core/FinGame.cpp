#include "FinEngine/Core/FinGame.h"

#include "FinEngine/Log.h"
#include "FinEngine/Platform/System/System.h"
#include "FinEngine/Platform/Graphics/Graphics.h"
#include "FinEngine/Rendering/Renderer2D.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory>
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
        graphics_.reset(Graphics::Create());

        system_->Init();
        graphics_->Init();

        Renderer2D::Init(graphics_.get());

        LOG_INFO("FinGame", "Game Initialized");
    }

    void FinGame::GameLoop() {
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
        }
    }

    void FinGame::ShutDown() {
        LOG_INFO("FinGame", "Shutting down");
        if (currentState) {
            currentState->destroy();
            delete currentState;
            currentState = nullptr;
        }

        Renderer2D::Shutdown();

        graphics_->Shutdown();
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