#pragma once
#include "lanes/Lane.h"

// Cars drive across; touching one kills the frog.
class RoadLane final : public Lane {
public:
    RoadLane(int row, float speed, int carCount);

    LaneOutcome Resolve(Frog& frog, float dt) const override;

protected:
    void DrawBackground() const override;
    void Wrap(Entity& entity) const override;

private:
    float loopLength_ = 0.0f;   // cars live on a conveyor of this length
};
