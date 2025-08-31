//
// Created by Cacahuète on 12/07/2023.
//

#ifndef LET_SOFTWAREKEYBOARD_H
#define LET_SOFTWAREKEYBOARD_H


#include <3ds.h>

class SoftwareKeyboard {
public:
    SoftwareKeyboard(SwkbdType type, int buttonCount, int maxTextLength);

    SoftwareKeyboard* setInitialText(const char* text);
    SoftwareKeyboard* setHintText(const char* text);
    SoftwareKeyboard* setButton(SwkbdButton index, const char* text, bool submit);
    SoftwareKeyboard* addFeatures(u32 features);
    SoftwareKeyboard* setFeatures(u32 features);
    SoftwareKeyboard* setNumpadKeys(char left, char right);

    SoftwareKeyboard* darkenTopScreen();
    SoftwareKeyboard* allowHome();
    SoftwareKeyboard* allowPower();
    SoftwareKeyboard* allowReset();

    int run();
    char* result();
private:
    SwkbdState m_state;
    char m_buffer[64];
    u32 m_features;
};


#endif
