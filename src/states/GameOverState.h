#pragma once
#include "core/GameState.h"

class GameOverState final : public GameState {
public:
    GameOverState(Game& game, int finalScore) : GameState(game), finalScore_(finalScore) {}

    void Update(float dt) override;
    void Draw() const override;

private:
    int finalScore_;
};
