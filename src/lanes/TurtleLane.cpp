#include "lanes/TurtleLane.h"
#include "entities/Turtle.h"
#include "entities/Frog.h"
#include "Config.h"
#include "Theme.h"

TurtleLane::TurtleLane(int row, float speed, int turtleCount) : Lane(row) {
    const float spacing = static_cast<float>(Config::ScreenW) / static_cast<float>(turtleCount);
    const float offset = static_cast<float>(GetRandomValue(0, static_cast<int>(spacing) - 1));

    for (int i = 0; i < turtleCount; ++i) {
        Add(std::make_unique<Turtle>(offset + spacing * static_cast<float>(i), row, speed));
    }
}

LaneOutcome TurtleLane::Resolve(Frog& frog, float) const {
    const Rectangle box = frog.HitBox();
    for (const auto& e : entities_) {
        if (e->IsDeadly() && CheckCollisionRecs(box, e->Bounds())) return LaneOutcome::Killed;
    }
    return LaneOutcome::Safe;
}

void TurtleLane::DrawBackground() const {
    DrawRectangle(0, row_ * Config::Cell, Config::ScreenW, Config::Cell, Theme::Shallows);
}

void TurtleLane::Wrap(Entity& e) const {
    const Rectangle& b = e.Bounds();
    if (e.Speed() > 0.0f && b.x > Config::ScreenW) e.SetX(-b.width);
    if (e.Speed() < 0.0f && b.x + b.width < 0.0f) e.SetX(static_cast<float>(Config::ScreenW));
}