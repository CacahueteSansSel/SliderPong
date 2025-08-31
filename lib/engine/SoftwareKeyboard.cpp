//
// Created by Cacahuète on 12/07/2023.
//

#include "SoftwareKeyboard.h"

SoftwareKeyboard::SoftwareKeyboard(SwkbdType type, int buttonCount, int maxTextLength) {
    swkbdInit(&m_state, type, buttonCount, maxTextLength);
}

SoftwareKeyboard* SoftwareKeyboard::setInitialText(const char *text) {
    swkbdSetInitialText(&m_state, text);

    return this;
}

SoftwareKeyboard* SoftwareKeyboard::setHintText(const char *text) {
    swkbdSetHintText(&m_state, text);

    return this;
}

int SoftwareKeyboard::run() {
    swkbdSetFeatures(&m_state, m_features);

    return swkbdInputText(&m_state, m_buffer, sizeof(m_buffer));
}

SoftwareKeyboard* SoftwareKeyboard::setButton(SwkbdButton index, const char *text, bool submit) {
    swkbdSetButton(&m_state, index, text, submit);

    return this;
}

char *SoftwareKeyboard::result() {
    return m_buffer;
}

SoftwareKeyboard* SoftwareKeyboard::darkenTopScreen() {
    addFeatures(SWKBD_DARKEN_TOP_SCREEN);

    return this;
}

SoftwareKeyboard* SoftwareKeyboard::addFeatures(u32 features) {
    m_features |= features;

    return this;
}

SoftwareKeyboard* SoftwareKeyboard::setFeatures(u32 features) {
    m_features = features;

    return this;
}

SoftwareKeyboard* SoftwareKeyboard::allowHome() {
    addFeatures(SWKBD_ALLOW_HOME);

    return this;
}

SoftwareKeyboard* SoftwareKeyboard::allowPower() {
    addFeatures(SWKBD_ALLOW_POWER);

    return this;
}

SoftwareKeyboard* SoftwareKeyboard::allowReset() {
    addFeatures(SWKBD_ALLOW_RESET);

    return this;
}

SoftwareKeyboard *SoftwareKeyboard::setNumpadKeys(char left, char right) {
    swkbdSetNumpadKeys(&m_state, left, right);

    return this;
}
