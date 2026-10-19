#pragma once
#include "entities/Entity.h"
#include "Config.h"

enum class TurtleState { Disabled, Enabled };

// Enemy: touching it sends the frog back to the start.
class Turtle final : public Entity {
public:
    static constexpr float Size = static_cast<float>(Config::Cell - 10);

    Turtle(float x, int row, float speed);

    void Update(float dt) override;
    void Draw() const override;

    bool IsDeadly() const override { return state_ == TurtleState::Enabled; }

    TurtleState State() const { return state_; }
    bool IsWarning() const { return state_ == TurtleState::Disabled && timer_ <= Config::TurtleWarnTime; }

private:
    void Enter(TurtleState state);
    void DrawEnabledLook(float alpha) const;
    void DrawDisabledLook() const;

    TurtleState state_ = TurtleState::Disabled;
    float timer_ = 0.0f;             // seconds left in the current state
};