#include "states/GameOverState.h"
#include "core/Game.h"
#include "states/PlayingState.h"
#include "states/OptionsState.h"
#include "ui/TextUtils.h"

void GameOverState::Update(float) {
    if (IsKeyPressed(KEY_R) || IsKeyPressed(KEY_ENTER)) game_.ChangeState<PlayingState>();
    if (IsKeyPressed(KEY_O)) game_.ChangeState<OptionsState>();
}

void GameOverState::Draw() const {
    DrawCenteredText("GAME OVER", 200, 70, RED);
    DrawCenteredText(TextFormat("Final score: %d", finalScore_), 290, 30, WHITE);
    DrawCenteredText("Press R to play again", 340, 24, LIGHTGRAY);
    DrawCenteredText("Press O for how to play", 375, 22, SKYBLUE);
}
