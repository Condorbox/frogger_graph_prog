#include "ui/Hud.h"
#include "core/GameSession.h"
#include "entities/Frog.h"
#include "Config.h"
#include "raylib.h"

void Hud::Draw(const GameSession& s) const {
    const int y = Config::HudRow * Config::Cell;
    DrawRectangle(0, y, Config::ScreenW, Config::Cell, BLACK);

    DrawText("LIVES", 10, y + 15, 20, WHITE);
    for (int i = 0; i < s.Lives(); ++i) {
        Frog::DrawShape(105.0f + 32.0f * static_cast<float>(i), static_cast<float>(y + 27), 11.0f);
    }

    DrawText(TextFormat("TIME %02ds / %02ds", static_cast<int>(s.Elapsed()), static_cast<int>(Config::LevelTime)),
             230, y + 15, 20, WHITE);
    const float ratio = s.TimeLeftRatio();
    DrawRectangle(450, y + 17, 150, 16, DARKGRAY);
    DrawRectangle(450, y + 17, static_cast<int>(150.0f * ratio), 16, ratio > 0.25f ? GREEN : RED);

    DrawText(TextFormat("LVL %d   SCORE %d", s.Level(), s.Score()), 620, y + 15, 20, WHITE);
}
