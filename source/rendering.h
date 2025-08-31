//
// Created by Cacahuète on 09/06/2023.
//

#ifndef INC_3DSBUILDTEMPLATE_RENDERING_H
#define INC_3DSBUILDTEMPLATE_RENDERING_H

#include <citro2d.h>

namespace rendering {
    void init();
    C2D_Text* createText(const char* text);
    void drawText(const char* text, float x, float y, float size = 1, u32 color = 0x000000FF);
    void drawTextCentered(const char* text, float x, float y, float width, float height, float size, float yOffset, u32 color);
    void frameEnd();
    void clearTextBuffer();
}

#endif //INC_3DSBUILDTEMPLATE_RENDERING_H
