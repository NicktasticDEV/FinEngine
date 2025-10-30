#include "System_Wii.h"
#include "FinEngine/Log.h"

#include <gccore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace FinEngine {

    GXRModeObj* System_Wii::rmode = nullptr;
    void* System_Wii::xfb[2] = {nullptr, nullptr};
    int System_Wii::currentXfb = 0;

    void System_Wii::Init() {
        LOG_INFO("System_Wii", "Initializing");

        // Initialise the video system
        VIDEO_Init();

        // Obtain the preferred video mode from the system
        // This will correspond to the settings in the Wii menu
        rmode = VIDEO_GetPreferredMode(NULL);

        // Allocate memory for the display in the uncached region
        xfb[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
        xfb[1] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

        // Initialise the console, required for printf
        // Initialize console on the first framebuffer
        console_init(xfb[0], 20, 20, rmode->fbWidth - 20, rmode->xfbHeight - 20, rmode->fbWidth * VI_DISPLAY_PIX_SZ);
        SYS_STDIO_Report(true);

        // Set up the video registers with the chosen mode
        VIDEO_Configure(rmode);

        // Tell the video hardware where our display memory is
        VIDEO_SetNextFramebuffer(xfb[0]);

        // Clear the framebuffer
        VIDEO_ClearFrameBuffer(rmode, xfb[0], COLOR_BLACK);

        // Make the display visible
        VIDEO_SetBlack(false);

        // Flush the video register changes to the hardware
        VIDEO_Flush();

        // Wait for Video setup to complete
        VIDEO_WaitVSync();
        if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

        LOG_INFO("System_Wii", "System Initialized");
    }

    void System_Wii::Shutdown() {
        LOG_INFO("System_Wii", "Shutting down");
        // Set the screen to black
        VIDEO_SetBlack(true);

        if (xfb[0]) {
            void* cached = MEM_K1_TO_K0(xfb[0]);
            free(cached);
            xfb[0] = NULL;
        }
        if (xfb[1]) {
            void* cached = MEM_K1_TO_K0(xfb[1]);
            free(cached);
            xfb[1] = NULL;
        }

        rmode = NULL;
    }

}