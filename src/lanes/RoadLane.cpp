#include "lanes/RoadLane.h"
#include "entities/Car.h"
#include "entities/Frog.h"
#include "Config.h"
#include "Theme.h"
#include <cmath>

RoadLane::RoadLane(int row, float speed, int carCount) : Lane(row) {
    const Color palette[] = { RED, ORANGE, YELLOW, SKYBLUE, PINK, WHITE };
    const auto n = static_cast<std::size_t>(carCount);

    // 1) Pick a sprite for every car; the widths decide the layout.
    std::vector<int> variants(n);
    std::vector<float> widths(n);
    float totalWidth = 0.0f, maxWidth = 0.0f;
    for (std::size_t i = 0; i < n; ++i) {
        variants[i] = GetRandomValue(0, Car::VariantCount - 1);
        widths[i] = Car::WidthFor(variants[i]);
        totalWidth += widths[i];
        maxWidth = std::max(maxWidth, widths[i]);
    }

    // 2) The loop must be long enough that a wrapping car is fully off screen,
    //    and that every car still has at least MinCarGap behind it.
    const float minLoop = static_cast<float>(Config::ScreenW) + maxWidth;
    const float minForGaps = totalWidth + static_cast<float>(carCount) * Config::MinCarGap;
    loopLength_ = std::max(minLoop, minForGaps);

    // 3) Hand out the leftover space as random extra gap between cars.
    const float slack = loopLength_ - minForGaps;
    std::vector<float> weights(n);
    float weightSum = 0.0f;
    for (float& w : weights) {
        w = 0.5f + static_cast<float>(GetRandomValue(0, 100)) / 100.0f;
        weightSum += w;
    }

    // 4) Place the cars one after another, then fold them into the visible window.
    float cursor = static_cast<float>(GetRandomValue(0, static_cast<int>(loopLength_) - 1));
    for (std::size_t i = 0; i < n; ++i) {
        const float x = std::fmod(cursor + maxWidth, loopLength_) - maxWidth;
        Add(std::make_unique<Car>(x, row, variants[i], speed, palette[GetRandomValue(0, 5)]));
        cursor += widths[i] + Config::MinCarGap + slack * weights[i] / weightSum;
    }
}

LaneOutcome RoadLane::Resolve(Frog& frog, float) const {
    const Rectangle box = frog.HitBox();
    for (const auto& e : entities_) {
        if (CheckCollisionRecs(box, e->Bounds())) return LaneOutcome::Killed;
    }
    return LaneOutcome::Safe;
}

void RoadLane::DrawBackground() const {
    DrawRectangle(0, row_ * Config::Cell, Config::ScreenW, Config::Cell, Theme::Road);
}

void RoadLane::Wrap(Entity& e) const {
    const Rectangle& b = e.Bounds();
    // Every car jumps by the same amount, so the gaps between them never change.
    if (e.Speed() > 0.0f && b.x > Config::ScreenW)          e.ShiftX(-loopLength_);
    else if (e.Speed() < 0.0f && b.x + b.width < 0.0f)      e.ShiftX(loopLength_);
}
