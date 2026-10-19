#pragma once
#include "entities/Frog.h"
#include "lanes/Lane.h"
#include "world/GoalRow.h"
#include "world/WorldTypes.h"
#include <memory>
#include <vector>

// The simulation: frog + goal row + lanes. It knows nothing about lives,
// score or timers; it only reports what happened through an event queue.
class World {
public:
    World();

    void StartLevel(int level);
    bool HopFrog(Direction dir);
    void ResetFrog() { frog_.Reset(); }

    void Update(float dt);
    void Draw() const;

    std::vector<WorldEvent> ConsumeEvents();

private:
    const Lane* LaneAt(int row) const;   // nullptr for the goal row

    Frog frog_;
    GoalRow goal_;
    std::vector<std::unique_ptr<Lane>> lanes_;
    std::vector<WorldEvent> events_;
};
