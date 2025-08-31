#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <time.h>
#include "libs.h"
#include "loop.h"
#include "utils.h"

bool mainExit = false;
C3D_RenderTarget* top;
C3D_RenderTarget* bottom;

void renderTopScreen() {
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

    C3D_RenderTargetClear(top, C3D_CLEAR_ALL, 0x000000FF, 0);
    C3D_FrameDrawOn(top);
    C2D_SceneTarget(top);

    renderTop();

    C3D_FrameEnd(0);
}

void renderBottomScreen() {
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

    C3D_RenderTargetClear(bottom, C3D_CLEAR_ALL, 0x000000FF, 0);
    C3D_FrameDrawOn(bottom);
    C2D_SceneTarget(bottom);

    renderBottom();

    C3D_FrameEnd(0);
}

int main(int argc, char* argv[])
{
    gfxInitDefault();
    cfguInit();
    aptInit();
    amInit();
    ptmuInit();
    osSetSpeedupEnable(true);
    ptmSysmInit();
    ndspInit();
    romfsInit();

    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    startInit();

	// Main loop
	while (aptMainLoop() && !mainExit)
	{
		hidScanInput();

        if (!update()) break;

        // Render Top Screen
        renderTopScreen();
        // Render Bottom Screen
        renderBottomScreen();
	}

	end();

    amExit();
    ptmSysmExit();
    C3D_Fini();
    C2D_Fini();
    romfsExit();
    cfguExit();
    aptExit();
    ptmuExit();
    gfxExit();
    ndspExit();
	return 0;
}
