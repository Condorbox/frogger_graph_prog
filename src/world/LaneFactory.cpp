#include "world/LaneFactory.h"
#include "lanes/RiverLane.h"
#include "lanes/RoadLane.h"
#include "lanes/SafeLane.h"
#include "Config.h"
#include "Theme.h"

namespace {
struct RiverSpec { LogType type; float speed; float gapCells; };

// One entry per river row (row 1, 2, 3): one log type each, different speeds.
constexpr RiverSpec kRiverSpecs[] = {
    { LogType::Log2U, 110.0f, 2.0f },
    { LogType::Log4U,  60.0f, 2.5f },
    { LogType::Log1U,  85.0f, 1.5f },
};
}  // namespace

std::vector<std::unique_ptr<Lane>> LaneFactory::BuildLevel(int level) {
    const float mult = 1.0f + Config::SpeedGrowthPerLevel * static_cast<float>(level - 1);

    std::vector<std::unique_ptr<Lane>> lanes;
    for (int row = Config::RiverFirstRow; row <= Config::StartRow; ++row) {
        if (Config::IsRiverRow(row)) {
            const RiverSpec& s = kRiverSpecs[row - Config::RiverFirstRow];
            lanes.push_back(std::make_unique<RiverLane>(row, s.type, s.speed * mult, s.gapCells));
        } else if (Config::IsRoadRow(row)) {
            const float dir = (row % 2 == 0) ? 1.0f : -1.0f;
            const float speed = dir * static_cast<float>(70 + GetRandomValue(0, 70)) * mult;
            lanes.push_back(std::make_unique<RoadLane>(row, speed, 3));
        } else {
            lanes.push_back(std::make_unique<SafeLane>(row, Theme::Safe));
        }
    }
    return lanes;
}
