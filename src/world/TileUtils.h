#pragma once
#include "Config.h"
#include "core/ResourceManager.h"
#include "raylib.h"

// Fills one full-width row with a square tile (one Cell x Cell sprite per column).
// If the texture is missing, the row is filled with `fallback` instead.
inline void DrawTiledRow(int row, TextureId tile, Color fallback) {
    const int y = row * Config::Cell;
    const ResourceManager& res = ResourceManager::Instance();

    if (!res.Has(tile)) {
        DrawRectangle(0, y, Config::ScreenW, Config::Cell, fallback);
        return;
    }

    const Texture2D& t = res.Get(tile);
    const Rectangle src{ 0.0f, 0.0f, static_cast<float>(t.width), static_cast<float>(t.height) };
    for (int col = 0; col < Config::Cols; ++col) {
        const Rectangle dst{ static_cast<float>(col * Config::Cell), static_cast<float>(y),
                             static_cast<float>(Config::Cell), static_cast<float>(Config::Cell) };
        DrawTexturePro(t, src, dst, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
    }
}