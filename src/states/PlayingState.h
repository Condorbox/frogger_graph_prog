#pragma once
#include "core/GameSession.h"
#include "core/GameState.h"
#include "ui/Hud.h"
#include "world/World.h"

// Glue between input, the World (simulation), the GameSession (rules) and audio.
class PlayingState final : public GameState {
public:
    using GameState::GameState;

    void OnEnter() override;
    void Update(float dt) override;
    void Draw() const override;

private:
    void HandleInput();
    void ProcessWorldEvents();
    void LoseLife(bool drowned);

    GameSession session_;
    World world_;
    Hud hud_;
};
