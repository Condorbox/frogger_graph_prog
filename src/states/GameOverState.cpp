#include "states/GameOverState.h"
#include "core/Game.h"
#include "states/PlayingState.h"
#include "ui/TextUtils.h"

void GameOverState::Update(float) {
    if (IsKeyPressed(KEY_R) || IsKeyPressed(KEY_ENTER)) game_.ChangeState<PlayingState>();
}

void GameOverState::Draw() const {
    DrawCenteredText("GAME OVER", 200, 70, RED);
    DrawCenteredText(TextFormat("Final score: %d", finalScore_), 290, 30, WHITE);
    DrawCenteredText("Press R to play again", 340, 24, LIGHTGRAY);
}
