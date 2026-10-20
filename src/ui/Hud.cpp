#include "ui/Hud.h"
#include "core/GameSession.h"
#include "entities/Frog.h"
#include "Config.h"
#include "raylib.h"

void Hud::Draw(const GameSession& s) const {
    const int y = Config::HudRow * Config::Cell;
    const int textY = y + 15;
    DrawRectangle(0, y, Config::ScreenW, Config::Cell, BLACK);

    int x = Config::HUD::Pad;

    // Lives
    DrawText("LIVES", x, textY, Config::HUD::FontSize, WHITE);
    x += MeasureText("LIVES", Config::HUD::FontSize) + 12;
    for (int i = 0; i < s.Lives(); ++i) {
        Frog::DrawShape(static_cast<float>(x + Config::HUD::LifeSlot / 2 + Config::HUD::LifeSlot * i),
            static_cast<float>(y + 27), Config::HUD::LifeSize);
    }
    x += Config::HUD::LifeSlot * Config::MaxLives + Config::HUD::Gap;

    // Timer: text followed by the bar.
    const char* timeText = TextFormat("TIME %02ds / %02ds",
        static_cast<int>(s.Elapsed()), static_cast<int>(Config::LevelTime));
    DrawText(timeText, x, textY, Config::HUD::FontSize, WHITE);
    x += MeasureText(timeText, Config::HUD::FontSize) + 10;

    const float ratio = s.TimeLeftRatio();
    DrawRectangle(x, y + 17, Config::HUD::BarWidth, Config::HUD::BarHeight, DARKGRAY);
    DrawRectangle(x, y + 17, static_cast<int>(static_cast<float>(Config::HUD::BarWidth) * ratio), Config::HUD::BarHeight,
        ratio > 0.25f ? GREEN : RED);

    // Level and score: right-aligned, so it can never run off the screen
    const char* info = TextFormat("LVL %d   SCORE %d", s.Level(), s.Score());
    DrawText(info, Config::ScreenW - Config::HUD::Pad - 
        MeasureText(info, Config::HUD::FontSize), textY, Config::HUD::FontSize, WHITE);
}
