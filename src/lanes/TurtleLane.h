#pragma once
#include "lanes/Lane.h"

// Turtles patrol across the lane; touching one kills the frog.
// The rest of the lane is walkable.
class TurtleLane final : public Lane {
public:
    TurtleLane(int row, float speed, int turtleCount = 1);

    LaneOutcome Resolve(Frog& frog, float dt) const override;

protected:
    void DrawBackground() const override;
    void Wrap(Entity& entity) const override;
};