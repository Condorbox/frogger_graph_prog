#include "lanes/RoadLane.h"
#include "entities/Car.h"
#include "entities/Frog.h"
#include "Config.h"
#include "Theme.h"

RoadLane::RoadLane(int row, float speed, int carCount) : Lane(row) {
    const Color palette[] = { RED, ORANGE, YELLOW, SKYBLUE, PINK, WHITE };
    const float spacing = static_cast<float>(Config::ScreenW) / static_cast<float>(carCount);
    const float offset = static_cast<float>(GetRandomValue(0, static_cast<int>(spacing) - 1));

    for (int i = 0; i < carCount; ++i) {
        const float width = static_cast<float>(Config::Cell * GetRandomValue(1, 2));
        const Rectangle bounds{ offset + spacing * static_cast<float>(i),
                                static_cast<float>(row * Config::Cell + 8),
                                width,
                                static_cast<float>(Config::Cell - 16) };
        Add(std::make_unique<Car>(bounds, speed, palette[GetRandomValue(0, 5)]));
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
    if (e.Speed() > 0.0f && b.x > Config::ScreenW) e.SetX(-b.width);
    if (e.Speed() < 0.0f && b.x + b.width < 0.0f) e.SetX(static_cast<float>(Config::ScreenW));
}
