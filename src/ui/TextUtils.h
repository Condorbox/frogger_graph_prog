#pragma once
#include "Config.h"
#include "raylib.h"

inline void DrawCenteredText(const char* text, int y, int size, Color color) {
    DrawText(text, Config::ScreenW / 2 - MeasureText(text, size) / 2, y, size, color);
}
