#include "world/World.h"
#include "world/LaneFactory.h"
#include "Config.h"
#include <utility>

World::World() {
    StartLevel(1);
}

void World::StartLevel(int level) {
    lanes_ = LaneFactory::BuildLevel(level);
    goal_.Reset();
    frog_.Reset();
}

const Lane* World::LaneAt(int row) const {
    if (row < Config::RiverFirstRow || row > Config::StartRow) return nullptr;
    return lanes_[static_cast<std::size_t>(row - Config::RiverFirstRow)].get();
}

bool World::HopFrog(Direction dir) {
    // The goal row can only be entered through a free exit.
    if (dir == Direction::Up && frog_.Row() == Config::GoalRow + 1 && !goal_.CanEnter(frog_)) {
        return false;
    }
    if (!frog_.Hop(dir)) return false;

    events_.push_back(WorldEvent::FrogHopped);

    if (frog_.Row() == Config::GoalRow) {
        goal_.Occupy(frog_);
        frog_.Reset();
        events_.push_back(WorldEvent::SlotFilled);
        if (goal_.AllFilled()) events_.push_back(WorldEvent::LevelCleared);
        return true;
    }

    if (!Config::IsLogRow(frog_.Row())) frog_.SnapToGrid();   // only log lanes allow off-grid positions
    return true;
}

void World::Update(float dt) {
    frog_.Update(dt);

    for (auto& lane : lanes_) lane->Update(dt);

    if (const Lane* lane = LaneAt(frog_.Row())) {
        switch (lane->Resolve(frog_, dt)) {
            case LaneOutcome::Killed:
                events_.push_back(WorldEvent::FrogKilled);
                frog_.Reset();
                break;
            case LaneOutcome::Drowned:
                events_.push_back(WorldEvent::FrogDrowned);
                frog_.Reset();
                break;
            case LaneOutcome::Safe:
                break;
        }
    }
}

void World::Draw() const {
    goal_.Draw();
    for (const auto& lane : lanes_) lane->Draw();
    frog_.Draw();
}

std::vector<WorldEvent> World::ConsumeEvents() {
    return std::exchange(events_, {});
}
