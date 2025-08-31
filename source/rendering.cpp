//
// Created by Cacahuète on 09/06/2023.
//

#include "rendering.h"

#include <3ds/services/cfgu.h>

namespace rendering {

    C2D_TextBuf staticBuf;
    C2D_Font font;
    C2D_Text *texts[256];
    int textCall = 0;

    void init() {
        font = C2D_FontLoadSystem(CFG_REGION_EUR);
        staticBuf = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer
    }

    C2D_Text * createText(const char *text) {
        C2D_Text *t = new C2D_Text;

        C2D_TextFontParse(t, font, staticBuf, text);
        C2D_TextOptimize(t);

        return t;
    }

    void drawText(const char *text, float x, float y, float size, u32 color) {
        C2D_Text *t = texts[textCall];
        if (!t) {
            t = new C2D_Text;

            C2D_TextFontParse(t, font, staticBuf, text);
            C2D_TextOptimize(t);

            texts[textCall] = t;
        }

        C2D_DrawText(t, C2D_WithColor, x, y, 0.0f, size, size,
                     color);
        textCall++;
    }

    void drawTextCentered(const char* text, float x, float y, float width, float height, float size, float yOffset, u32 color) {
        C2D_Text *t = texts[textCall];
        if (!t) {
            t = new C2D_Text;

            C2D_TextFontParse(t, font, staticBuf, text);
            C2D_TextOptimize(t);

            texts[textCall] = t;
        }

        int tx = x + width / 2 - (t->width*size) / 2;
        int ty = y + height / 2 + yOffset;

        C2D_DrawText(t, C2D_WithColor, tx, ty, 0.0f, size, size,
                     color);
        textCall++;
    }

    void frameEnd() {
        textCall = 0;
    }

    void clearTextBuffer() {
        C2D_TextBufClear(staticBuf);
        for (int i = 0; i < 256; i++) {
            delete texts[i];
        }
        textCall = 0;
    }
}
