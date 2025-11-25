#include "Graphics_GX.h"

#include "FinEngine/Platform/System/Wii/System_Wii.h"
#include "FinEngine/Log.h"

#include <gccore.h>
#include <ogc/conf.h>

#define DEFAULT_FIFO_SIZE (256*1024)

namespace FinEngine {

    void Graphics_GX::Init() {
        LOG_INFO("Graphics_GX", "Initializing");
        // Initialize the GX graphics system
        static u8 fifo[DEFAULT_FIFO_SIZE] ATTRIBUTE_ALIGN(32);
        GX_Init(fifo, DEFAULT_FIFO_SIZE);
        GX_SetCopyClear((GXColor){ 0, 0, 0, 0 }, GX_MAX_Z24);

        u16 fbw = System_Wii::rmode->fbWidth;
        u16 efbh = System_Wii::rmode->efbHeight;

        GX_SetViewport(0.0f, 0.0f, (f32)fbw, (f32)efbh, 0.0f, 1.0f);
        GX_SetScissor(0, 0, fbw, efbh);
        GX_SetDispCopySrc(0, 0, fbw, efbh);
        GX_SetDispCopyDst(fbw, efbh);
        GX_SetCopyFilter(System_Wii::rmode->aa, System_Wii::rmode->sample_pattern, GX_TRUE, System_Wii::rmode->vfilter);
        GX_SetFieldMode(System_Wii::rmode->field_rendering,
                        (System_Wii::rmode->viHeight == 2 * System_Wii::rmode->xfbHeight) ? GX_ENABLE : GX_DISABLE);

        if (System_Wii::rmode->aa) {
            GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
        } else {
            GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
        }
        GX_SetDispCopyGamma(GX_GM_1_0);

        LOG_INFO("Graphics_GX", "Width: " + std::to_string(fbw) + ", height: " + std::to_string(efbh));

        if (CONF_GetAspectRatio() == CONF_ASPECT_16_9) {
            LOG_INFO("Graphics_GX", "Aspect Ratio: 16:9");
        } else if (CONF_GetAspectRatio() == CONF_ASPECT_4_3) {
            LOG_INFO("Graphics_GX", "Aspect Ratio: 4:3");
        } else {
            LOG_INFO("Graphics_GX", "Aspect Ratio: Unknown");
        }

        LOG_INFO("Graphics_GX", "Graphics Initialized");
    }

    void Graphics_GX::Shutdown() {
        LOG_INFO("Graphics_GX", "Shutting down");

        GX_DrawDone();
        GX_AbortFrame();
    }

    void Graphics_GX::TestDraw() {
        // Simple test draw function to clear the screen with a color
        // Important: You must copy the EFB to the XFB each frame, otherwise you'll flip to
        // an uninitialized buffer and see flashing.

        // Choose the buffer we'll display next
        int next = 1 - System_Wii::currentXfb;

        // Clear color set for the EFB copy; alpha 0xFF for opaque
        GX_SetCopyClear((GXColor){ 51, 76, 76, 0xFF }, GX_MAX_Z24);
        GX_SetColorUpdate(GX_TRUE);
        GX_SetAlphaUpdate(GX_TRUE);

        // Copy the EFB to the XFB we plan to display
        GX_CopyDisp(System_Wii::xfb[next], GX_TRUE); // GX_TRUE clears EFB after copy
        GX_DrawDone();

        // Tell VI to display that XFB
        VIDEO_SetNextFramebuffer(System_Wii::xfb[next]);
        VIDEO_Flush();
        VIDEO_WaitVSync();
        if (System_Wii::rmode->viTVMode & VI_NON_INTERLACE) {
            VIDEO_WaitVSync();
        }

        // Update current buffer index for next frame
        System_Wii::currentXfb = next;
    }

}