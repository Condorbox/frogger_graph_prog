#include "states/OptionsState.h"
#include "core/Game.h"
#include "states/TitleState.h"
#include "ui/TextUtils.h"
#include "Config.h"
#include "Theme.h"

namespace {
    constexpr int MarginX = 70;
    constexpr int BodyIndent = 15;
    constexpr int HeadSize = 24;
    constexpr int BodySize = 20;
    constexpr int LineHeight = 26;
    constexpr int SectionGap = 14;

    void Heading(const char* text, int& y, Color color) {
        DrawText(text, MarginX, y, HeadSize, color);
        y += LineHeight + 4;
    }

    void Line(const char* text, int& y) {
        DrawText(text, MarginX + BodyIndent, y, BodySize, LIGHTGRAY);
        y += LineHeight;
    }
}  // namespace

void OptionsState::Update(float) {
    if (IsKeyPressed(KEY_O)) game_.ChangeState<TitleState>();
}

void OptionsState::Draw() const {
    DrawCenteredText("HOW TO PLAY", 25, 44, LIME);

    int y = 100;

    Heading("GOAL", y, YELLOW);
    Line("Guide the frog to the top and fill every exit.", y);
    Line(TextFormat("You have %d lives and %d seconds per level.",
        Config::MaxLives, static_cast<int>(Config::LevelTime)), y);
    y += SectionGap;

    Heading("CONTROLS", y, YELLOW);
    Line("Arrows or WASD: hop one cell in that direction.", y);
    y += SectionGap;

    Heading("DANGERS", y, YELLOW);
    Line("Road: touching a car costs you a life.", y);
    Line("River: stay on a log, it carries you along.", y);
    Line("Water, or being carried off the screen, drowns you.", y);
    Line("Light-blue lanes are walkable, but turtles lurk there.", y);
    Line("Turtles hide (harmless), blink as a warning, then surface", y);
    Line("and kill you. Keep moving!", y);
    y += SectionGap;

    Heading("SCORE", y, YELLOW);
    Line(TextFormat("%d points per exit filled.", Config::SlotPoints), y);
    Line(TextFormat("Clearing a level: %d bonus + %d per second left.",
        Config::LevelBonus, Config::TimeBonusPerSecond), y);
    Line(TextFormat("Every level the traffic gets %d%% faster.",
        static_cast<int>(Config::SpeedGrowthPerLevel * 100.0f + 0.5f)), y);

    DrawCenteredText("Press O to go back to the title", Config::ScreenH - 80, 24, WHITE);
}