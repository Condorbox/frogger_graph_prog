#include "states/TitleState.h"
#include "core/Game.h"
#include "entities/Frog.h"
#include "states/PlayingState.h"
#include "states/OptionsState.h"
#include "ui/TextUtils.h"

void TitleState::Update(float) {
    if (IsKeyPressed(KEY_ENTER)) game_.ChangeState<PlayingState>();
    if (IsKeyPressed(KEY_O))     game_.ChangeState<OptionsState>();
}

void TitleState::Draw() const {
    Frog::DrawShape(Config::ScreenW / 2.0f, 110.0f, 40.0f);
    DrawCenteredText("FROGGER", 180, 80, LIME);
    DrawCenteredText("Press ENTER to start", 300, 28, WHITE);
    DrawCenteredText("Press O for how to play", 345, 22, SKYBLUE);
    DrawCenteredText("Arrows / WASD to hop", 395, 20, LIGHTGRAY);
    DrawCenteredText(TextFormat("Fill all %d exits within %d seconds",
        Config::NumSlots, static_cast<int>(Config::LevelTime)),
        425, 20, LIGHTGRAY);
}
