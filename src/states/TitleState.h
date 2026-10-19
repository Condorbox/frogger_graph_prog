#pragma once
#include "core/GameState.h"

class TitleState final : public GameState {
public:
    using GameState::GameState;

    void Update(float dt) override;
    void Draw() const override;
};
