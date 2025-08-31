//
// Created by Cacahuète on 10/03/2024.
//

#include "loop.h"
#include "rendering.h"
#include "utils.h"
#include "engine/Texture.h"

struct rect {
    float x, y, w, h;
};

float leftSliderValue = 0.5f;
float rightSliderValue = 0.75f;
float ballX = 10;
float ballY = 0;
float ballDirX = 1;
float ballDirY = 1;
rect leftPaddle = {0, 0, 10, 50};
rect rightPaddle = {400 - 10, 0, 10, 50};
float leftPaddleOffset = 0;
float rightPaddleOffset = 0;
float ballSpeed = 2.0f;
Texture* bottomScreenTexture;

void startInit() {
    rendering::init();

    bottomScreenTexture = new Texture("romfs:/textures/bottom_screen.png");
}

void renderTop() {
    C2D_DrawRectSolid(leftPaddle.x, leftPaddle.y, 0, leftPaddle.w, leftPaddle.h, 0xFFFFFFFF);
    C2D_DrawRectSolid(rightPaddle.x, rightPaddle.y, 0, leftPaddle.w, leftPaddle.h, 0xFFFFFFFF);

    C2D_DrawRectSolid(ballX, ballY, 0, 20, 20, 0xFF6793FF);
}

void renderBottom() {
    C2D_DrawImageAt(bottomScreenTexture->image(), 0, 0, 0);

    rendering::frameEnd();
}

void setRandomSpeed() {
    ballSpeed = 2 + static_cast<float>(rand() % 2 + 1);
}

void resetGame() {
    ballX = 10;
    ballY = 0;
    ballDirX = 1;
    ballDirY = 1;
}

bool update() {
    u8 volValue;
    HIDUSER_GetSoundVolume(&volValue);

    leftSliderValue = volValue / 63.0f;
    rightSliderValue = (osGet3DSliderState() - 0.1f) / 0.9f;
    if (rightSliderValue < 0) rightSliderValue = 0;

    float left = 1.0f - leftSliderValue;
    float right = 1.0f - rightSliderValue;
    leftPaddle.y = left * (240 - 50) + leftPaddleOffset;
    rightPaddle.y = right * (240 - 50) + rightPaddleOffset;

    if (keysHeld() & KEY_CPAD_DOWN) leftPaddleOffset += 4;
    if (keysHeld() & KEY_CPAD_UP) leftPaddleOffset -= 4;
    if (keysHeld() & KEY_CSTICK_DOWN) rightPaddleOffset += 4;
    if (keysHeld() & KEY_CSTICK_UP) rightPaddleOffset -= 4;

    ballX += ballDirX * ballSpeed;
    ballY += ballDirY * ballSpeed;

    if (ballX < -20) {
        resetGame();
    }
    if (ballY < 0) {
        ballDirY = 1;
        setRandomSpeed();
    }
    if (ballX >= 400) {
        resetGame();
    }
    if (ballY + 20 >= 240) {
        ballDirY = -1;
        setRandomSpeed();
    }

    if (ballX + 20 >= rightPaddle.x && ballY + 20 > rightPaddle.y && ballY < rightPaddle.y + rightPaddle.h) {
        ballDirX = -1;
        setRandomSpeed();
    }
    if (ballX <= leftPaddle.x + leftPaddle.w && ballY + 20 > leftPaddle.y && ballY < leftPaddle.y + leftPaddle.h) {
        ballDirX = 1;
        setRandomSpeed();
    }

    return true;
}

void end() {
    delete bottomScreenTexture;
}
