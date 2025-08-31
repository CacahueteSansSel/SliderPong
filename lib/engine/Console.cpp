#include "Console.h"
#include <3ds.h>
#include <stdio.h>

bool initialized = false;

void consolePrint(const char *text)
{
    if (!initialized) {
        consoleInit(GFX_TOP, NULL);
        initialized = true;
    }
    printf("%s\n", text);
}