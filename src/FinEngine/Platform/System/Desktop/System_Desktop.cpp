#include "System_Desktop.h"
#include "FinEngine/Log.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

namespace FinEngine {

    void System_Desktop::Init() {
        LOG_INFO("System", "Initializing for Desktop Platform");

        LOG_INFO("System", "System successfully initialized");
    }

    void System_Desktop::Shutdown() {
        LOG_INFO("System", "Shutting down");
    }

}