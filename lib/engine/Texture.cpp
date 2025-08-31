//
// Created by Cacahuète on 09/06/2023.
//

#include "Texture.h"
#include "../lodepng/lodepng.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>
#include <vector>
#include "libs.h"
#include "../../source/utils.h"

extern void consolePrint(const char *text);

// Code taken and edited from Universal Updater (filename source/utils/screenshot.cpp)
// https://github.com/Universal-Team/Universal-Updater

Texture::Texture(const char *filename) : m_isError(false) {
    std::vector<u8> ImageBuffer;
    unsigned int width, height;
    int e = lodepng::decode(ImageBuffer, width, height, filename);
    if (e != 0) {
        debugPrint(lodepng_error_text(e), filename);
        while (1) {}
    }

    m_width = width;
    m_height = height;

    m_img.tex = new C3D_Tex;
    m_img.subtex = new Tex3DS_SubTexture{(u16)m_width, (u16)m_height, 0.0f, 1.0f, m_width / 512.0f, 1.0f - (m_height / 512.0f)};

    int accurateSize = 512;

    C3D_TexInit(m_img.tex, accurateSize, accurateSize, GPU_RGBA8);
    C3D_TexSetFilter(m_img.tex, GPU_LINEAR, GPU_LINEAR);
    m_img.tex->border = 0;
    C3D_TexSetWrap(m_img.tex, GPU_CLAMP_TO_BORDER, GPU_CLAMP_TO_BORDER);

    for (u32 x = 0; x < m_width && x < accurateSize; x++) {
        for (u32 y = 0; y < m_height && y < accurateSize; y++) {
            const u32 dstPos = ((((y >> 3) * (accurateSize >> 3) + (x >> 3)) << 6) +
                                ((x & 1) | ((y & 1) << 1) | ((x & 2) << 1) | ((y & 2) << 2) |
                                 ((x & 4) << 2) | ((y & 4) << 3))) * 4;

            const u32 srcPos = (y * m_width + x) * 4;
            ((uint8_t *)m_img.tex->data)[dstPos + 0] = ImageBuffer.data()[srcPos + 3];
            ((uint8_t *)m_img.tex->data)[dstPos + 1] = ImageBuffer.data()[srcPos + 2];
            ((uint8_t *)m_img.tex->data)[dstPos + 2] = ImageBuffer.data()[srcPos + 1];
            ((uint8_t *)m_img.tex->data)[dstPos + 3] = ImageBuffer.data()[srcPos + 0];
        }
    }

    ImageBuffer.clear();
}

Texture::Texture(u8 *data, size_t size) {
    std::vector<u8> ImageBuffer;
    unsigned int width, height;
    lodepng::decode(ImageBuffer, width, height, data, size);

    m_width = width;
    m_height = height;

    m_img.tex = new C3D_Tex;
    m_img.subtex = new Tex3DS_SubTexture{(u16)m_width, (u16)m_height, 0.0f, 1.0f, m_width / 512.0f, 1.0f - (m_height / 512.0f)};

    int accurateSize = 512;

    C3D_TexInit(m_img.tex, accurateSize, accurateSize, GPU_RGBA8);
    C3D_TexSetFilter(m_img.tex, GPU_LINEAR, GPU_LINEAR);
    m_img.tex->border = 0xFFFFFFFF;
    C3D_TexSetWrap(m_img.tex, GPU_CLAMP_TO_BORDER, GPU_CLAMP_TO_BORDER);

    for (u32 x = 0; x < m_width && x < accurateSize; x++) {
        for (u32 y = 0; y < m_height && y < accurateSize; y++) {
            const u32 dstPos = ((((y >> 3) * (accurateSize >> 3) + (x >> 3)) << 6) +
                                ((x & 1) | ((y & 1) << 1) | ((x & 2) << 1) | ((y & 2) << 2) |
                                 ((x & 4) << 2) | ((y & 4) << 3))) * 4;

            const u32 srcPos = (y * m_width + x) * 4;
            ((uint8_t *)m_img.tex->data)[dstPos + 0] = ImageBuffer.data()[srcPos + 3];
            ((uint8_t *)m_img.tex->data)[dstPos + 1] = ImageBuffer.data()[srcPos + 2];
            ((uint8_t *)m_img.tex->data)[dstPos + 2] = ImageBuffer.data()[srcPos + 1];
            ((uint8_t *)m_img.tex->data)[dstPos + 3] = ImageBuffer.data()[srcPos + 0];
        }
    }

    ImageBuffer.clear();
}

C2D_Image Texture::image() {
    return m_img;
}

bool Texture::isError() {
    return m_isError;
}

const char *Texture::error() {
    return m_errorMessage;
}

int Texture::width() {
    return m_width;
}

int Texture::height() {
    return m_height;
}

void Texture::clear() {
    C3D_TexDelete(m_img.tex);
}

Texture::~Texture() {
    clear();
}
