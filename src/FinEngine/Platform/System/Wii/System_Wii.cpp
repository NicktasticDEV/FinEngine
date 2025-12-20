#include "System_Wii.h"
#include "FinEngine/Log.h"

#include <gccore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace FinEngine {

    void System_Wii::Init() {
        LOG_INFO("System", "Initializing for Wii platform");
        SYS_STDIO_Report(true);
    }

    void System_Wii::Shutdown() {

    }

}