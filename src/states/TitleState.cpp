#include "states/TitleState.h"
#include "core/Game.h"
#include "entities/Frog.h"
#include "states/PlayingState.h"
#include "ui/TextUtils.h"

void TitleState::Update(float) {
    if (IsKeyPressed(KEY_ENTER)) game_.ChangeState<PlayingState>();
}

void TitleState::Draw() const {
    Frog::DrawShape(Config::ScreenW / 2.0f, 110.0f, 40.0f);
    DrawCenteredText("FROGGER", 180, 80, LIME);
    DrawCenteredText("Press ENTER to start", 300, 28, WHITE);
    DrawCenteredText("Arrows / WASD to hop", 350, 20, LIGHTGRAY);
    DrawCenteredText("Fill all 5 exits before the minute runs out", 380, 20, LIGHTGRAY);
}
