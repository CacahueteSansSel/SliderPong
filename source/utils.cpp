//
// Created by Cacahuète on 09/06/2023.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <3ds.h>

bool isConsole = false;

void debugPrint(const char* text, const char* details) {
    if (!isConsole) {
        isConsole = true;
        consoleInit(GFX_TOP, nullptr);
    }

    printf("SLIDER PONG 3DS - Error occurred !\n");
    printf("Error: %s\n", text);
    if (details) printf("Details: %s\n", details);
    else printf("No further details\n");
    printf("Press any key to return to the HOME menu\n");

    while (aptMainLoop()) {
        hidScanInput();

        if (hidKeysDown()) break;
    }

    printf("Exitting...");

    exit(0);
}