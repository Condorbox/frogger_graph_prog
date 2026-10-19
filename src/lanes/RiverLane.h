#pragma once
#include "lanes/Lane.h"
#include "entities/Log.h"

// One type of log per lane, moving left -> right. The frog must stand on a log
// (and gets carried by it); anywhere else in the lane is water.
class RiverLane final : public Lane {
public:
    RiverLane(int row, LogType type, float speed, float gapCells);

    LaneOutcome Resolve(Frog& frog, float dt) const override;

protected:
    void DrawBackground() const override;
    void Wrap(Entity& entity) const override;

private:
    float loopLength_ = 0.0f;   // logs live on a conveyor of this length
};
