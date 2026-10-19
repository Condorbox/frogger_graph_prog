#pragma once
#include "lanes/Lane.h"

// A row with nothing dangerous on it (start row, median strip).
class SafeLane final : public Lane {
public:
    SafeLane(int row, Color color) : Lane(row), color_(color) {}

    LaneOutcome Resolve(Frog&, float) const override { return LaneOutcome::Safe; }

protected:
    void DrawBackground() const override;
    void Wrap(Entity&) const override {}

private:
    Color color_;
};
