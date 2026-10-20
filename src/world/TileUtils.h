#pragma once
#include "Config.h"
#include "core/ResourceManager.h"
#include "raylib.h"

// Draws one square tile at (col, row). If the texture is missing, the cell is
// filled with `fallback` instead.
inline void DrawTile(int col, int row, TextureId tile, Color fallback) {
    const Rectangle dst{ static_cast<float>(col * Config::Cell), static_cast<float>(row * Config::Cell),
                         static_cast<float>(Config::Cell), static_cast<float>(Config::Cell) };

    const ResourceManager& res = ResourceManager::Instance();
    if (!res.Has(tile)) {
        DrawRectangleRec(dst, fallback);
        return;
    }

    const Texture2D& t = res.Get(tile);
    DrawTexturePro(t,
        Rectangle{ 0.0f, 0.0f, static_cast<float>(t.width), static_cast<float>(t.height) },
        dst, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
}

// Fills one full-width row with a square tile (one Cell x Cell sprite per column).
inline void DrawTiledRow(int row, TextureId tile, Color fallback) {
    for (int col = 0; col < Config::Cols; ++col) DrawTile(col, row, tile, fallback);
}