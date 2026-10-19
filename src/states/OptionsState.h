#pragma once
#include "core/GameState.h"

// "How to play" screen. Opened with B from the title / game over screens,
// O returns to the title.
class OptionsState final : public GameState {
public:
    using GameState::GameState;

    void Update(float dt) override;
    void Draw() const override;
};