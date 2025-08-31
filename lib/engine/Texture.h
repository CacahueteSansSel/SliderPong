//
// Created by Cacahuète on 09/06/2023.
//

#ifndef INC_3DSBUILDTEMPLATE_PNGIMAGE_H
#define INC_3DSBUILDTEMPLATE_PNGIMAGE_H

#include <citro3d.h>
#include <citro2d.h>

class Texture {
public:
    Texture(const char* filename);
    Texture(u8* data, size_t size);
    ~Texture();

    C2D_Image image();
    bool isError();
    const char* error();
    int width();
    int height();
    void clear();
private:
    C2D_Image m_img;
    bool m_isError;
    const char* m_errorMessage;
    uint32_t m_width;
    uint32_t m_height;
};


#endif //INC_3DSBUILDTEMPLATE_PNGIMAGE_H
