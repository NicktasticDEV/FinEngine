#include "Graphics_GX.h"

#include "FinEngine/Platform/System/Wii/System_Wii.h"
#include "FinEngine/Platform/Windowing/Wii/Windowing_Wii.h"

#include "FinEngine/Log.h"

#include <gccore.h>
#include <ogc/conf.h>

#define DEFAULT_FIFO_SIZE (256*1024)

namespace FinEngine {

    void Graphics_GX::Init() {
        LOG_INFO("Graphics", "Initializing with GX backend");
        
        Mtx44 perspective;

        // ========================================
        // GX Initialization
        // ========================================
        static u8 fifo[DEFAULT_FIFO_SIZE] ATTRIBUTE_ALIGN(32);
        GX_Init(fifo, DEFAULT_FIFO_SIZE);
        GX_SetCopyClear((GXColor){ 0, 0, 0, 0 }, GX_MAX_Z24);

        u16 fbw = Windowing_Wii::rmode->fbWidth;
        u16 efbh = Windowing_Wii::rmode->efbHeight;

        GX_SetViewport(0.0f, 0.0f, (f32)fbw, (f32)efbh, 0.0f, 1.0f);
        GX_SetScissor(0, 0, fbw, efbh);

        GX_SetDispCopySrc(0, 0, fbw, efbh);
        GX_SetDispCopyDst(fbw, efbh);

        GX_SetCopyFilter(Windowing_Wii::rmode->aa, Windowing_Wii::rmode->sample_pattern, GX_TRUE, Windowing_Wii::rmode->vfilter);
        GX_SetFieldMode(Windowing_Wii::rmode->field_rendering, (Windowing_Wii::rmode->viHeight == 2 * Windowing_Wii::rmode->xfbHeight) ? GX_ENABLE : GX_DISABLE);

        if (Windowing_Wii::rmode->aa) {
            GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
        } else {
            GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
        }
        GX_SetCullMode(GX_CULL_NONE);
        GX_SetDispCopyGamma(GX_GM_1_0);

        // ========================================
        // Matrices
        // ========================================
        // Projection
        if (CONF_GetAspectRatio() == CONF_ASPECT_16_9) {
            guOrtho(perspective, 0.0f, 480, 0.0f, 854, 0.0f, 1000.0f);
        } 
        else {
            guOrtho(perspective, 0.0f, Windowing_Wii::rmode->efbHeight, 0.0f, Windowing_Wii::rmode->fbWidth, 0.0f, 1000.0f);
        }
        GX_LoadProjectionMtx(perspective, GX_ORTHOGRAPHIC);

        // ========================================
        // Other shit
        // ========================================
        GX_SetColorUpdate(GX_ENABLE);
        GX_SetAlphaUpdate(GX_TRUE);
        GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

        // TODO: This stuff should probably be handled on a per geometry basis
        /*
        // ========================================
        // Vertex data things
        // ========================================
        // Tells the flipper to expect direct data
        GX_ClearVtxDesc();
        GX_SetVtxDesc(GX_VA_POS,  GX_DIRECT);
        GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);

        // Set attributes for data
        GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS,  GX_POS_XYZ,  GX_F32, 0);
        GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST,   GX_F32, 0);
        GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);

        // ========================================
        // TEV
        // ========================================
        GX_SetNumChans(1);
        GX_SetNumTexGens(1);
        GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

        GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        */

        LOG_INFO("Graphics", "Graphics successfully initialized");
    }

    void Graphics_GX::Shutdown() {
        LOG_INFO("Graphics", "Shutting down");
        GX_DrawDone();
        GX_AbortFrame();
    }

    
    void Graphics_GX::BeginFrame() {

    }

    void Graphics_GX::EndFrame() {
        GX_DrawDone();

        Windowing_Wii::currentXfb ^= 1;

        GX_SetColorUpdate(GX_TRUE);
        GX_SetAlphaUpdate(GX_TRUE);

        // Copy the EFB to the currently selected XFB
        GX_CopyDisp(Windowing_Wii::xfb[Windowing_Wii::currentXfb], GX_TRUE);
        GX_DrawDone();
    }

    void Graphics_GX::ClearScreen() {
        GX_SetCopyClear((GXColor){ 0, 0, 0, 0 }, GX_MAX_Z24);
    }

}