#pragma once
#include "entities/Entity.h"
#include "Config.h"

// Enemy: touching it sends the frog back to the start.
class Turtle final : public Entity {
public:
    static constexpr float Size = static_cast<float>(Config::Cell - 10);

    Turtle(float x, int row, float speed);
    void Draw() const override;
};