#pragma once

#include <inc/types.h>

#include <string>
#include <vector>

struct Color {
    int R;
    int G;
    int B;
    int A;
};

const Color solidWhite = {255, 255, 255, 255};
const Color solidBlack = {0, 0, 0, 255};

const Color solidRed = {255, 0, 0, 255};
const Color solidGreen = {0, 255, 0, 255};
const Color solidBlue = {0, 0, 255, 255};

const Color solidPink = {255, 0, 255, 255};
const Color solidYellow = {255, 255, 0, 255};
const Color solidCyan = {0, 255, 255, 255};

const Color solidOrange = {255, 127, 0, 255};
const Color solidLime = {127, 255, 0, 255};
const Color solidPurple = {127, 0, 255, 255};

const Color transparentGray = {75, 75, 75, 75};

// Natives called
void showText(float x, float y, float scale, const std::string& text, int font = 0, const Color& rgba = solidWhite,
              bool outline = true);
void showDebugInfo3D(Vector3 location, std::vector<std::string> textLines, Color backgroundColor = transparentGray);
void showNotification(const std::string& message, int* prevNotification = nullptr);
void showSubtitle(const std::string& message, int duration = 2500);

bool FileExists(const std::string& name);
