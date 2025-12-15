#include "FinEngine/Rendering/Renderer2D.h"
#include "FinEngine/Log.h"

namespace FinEngine {

    Graphics* Renderer2D::s_Backend = nullptr;

    void Renderer2D::Init(Graphics* backend) {
        LOG_INFO("Renderer2D", "Initializing");
        s_Backend = backend;
        LOG_INFO("Renderer2D", "Initialized");
    }

    void Renderer2D::Shutdown() {
        LOG_INFO("Renderer2D", "Shutting down");
        s_Backend = nullptr;
        LOG_INFO("Renderer2D", "Shutdown complete");
    }

}