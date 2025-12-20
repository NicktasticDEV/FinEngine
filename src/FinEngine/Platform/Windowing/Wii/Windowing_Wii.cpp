#include "Windowing_Wii.h"
#include "FinEngine/Log.h"

namespace FinEngine {

    GXRModeObj* Windowing_Wii::rmode = nullptr;
    void* Windowing_Wii::xfb[2] = { nullptr, nullptr };
    int Windowing_Wii::currentXfb = 0;

    void Windowing_Wii::Init() {
        VIDEO_Init();

        currentXfb = 0;

        rmode = VIDEO_GetPreferredMode(NULL);

        xfb[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
        xfb[1] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

        VIDEO_Configure(rmode);

        VIDEO_SetNextFramebuffer(xfb[currentXfb]);
        VIDEO_ClearFrameBuffer(rmode, xfb[currentXfb], COLOR_BLACK);

        VIDEO_SetBlack(false);
        VIDEO_Flush();
        VIDEO_WaitVSync();
        if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
    }

    void Windowing_Wii::Shutdown() {
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

    void Windowing_Wii::Update() {
        currentXfb ^= 1;

        VIDEO_SetNextFramebuffer(xfb[currentXfb]);
        VIDEO_Flush();
        VIDEO_WaitVSync();
    }

}