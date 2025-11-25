#include "Audio_Wii.h"

#include <gccore.h>
#include <aesndlib.h>
#include <fat.h>
#include <audiogc.hpp>

#include "FinEngine/Log.h"

namespace FinEngine {

    void Audio_Wii::Init() {
        LOG_INFO("Audio_Wii", "Initializing");

        AESND_Init();

        LOG_INFO("Audio_Wii", "Initialized");
    }

    void Audio_Wii::Shutdown() {
        LOG_INFO("Audio_Wii", "Shutting down");
        
        LOG_INFO("Audio_Wii", "Shut Down");
    }

    void Audio_Wii::TestSound() {
        LOG_INFO("Audio_Wii", "Playing Test Sound");
        // Play a test sound here
    }

}