//
// Created by Cacahuète on 09/06/2023.
//

#ifndef INC_3DSBUILDTEMPLATE_UTILS_H
#define INC_3DSBUILDTEMPLATE_UTILS_H

#include <stdint.h>

struct BinaryFile {
    uint8_t* data;
    long size;
};

void debugPrint(const char* text, const char* details = nullptr);

#endif //INC_3DSBUILDTEMPLATE_UTILS_H
