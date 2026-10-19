#include "lanes/RiverLane.h"
#include "entities/Frog.h"
#include "Config.h"
#include "Theme.h"
#include <cmath>

RiverLane::RiverLane(int row, LogType type, float speed, float gapCells) : Lane(row) {
    const float width = Log::WidthFor(type);
    const float pitch = width + gapCells * Config::Cell;                       // distance between log starts
    const int count = static_cast<int>(std::ceil((Config::ScreenW + width) / pitch));
    loopLength_ = static_cast<float>(count) * pitch;
    const float offset = static_cast<float>(GetRandomValue(0, static_cast<int>(pitch)));

    for (int i = 0; i < count; ++i) {
        Add(std::make_unique<Log>(offset + static_cast<float>(i) * pitch - width, row, type, speed));
    }
}

LaneOutcome RiverLane::Resolve(Frog& frog, float dt) const {
    constexpr float forgiveness = 6.0f;
    const float cx = frog.CenterX();

    for (const auto& e : entities_) {
        const Rectangle& b = e->Bounds();
        if (cx >= b.x - forgiveness && cx <= b.x + b.width + forgiveness) {
            frog.CarryBy(e->Speed() * dt);
            const float newCx = frog.CenterX();
            if (newCx < 0.0f || newCx > Config::ScreenW) return LaneOutcome::Drowned;  // carried off screen
            return LaneOutcome::Safe;
        }
    }
    return LaneOutcome::Drowned;
}

void RiverLane::DrawBackground() const {
    DrawRectangle(0, row_ * Config::Cell, Config::ScreenW, Config::Cell, Theme::Water);
}

void RiverLane::Wrap(Entity& e) const {
    if (e.Bounds().x > Config::ScreenW) e.ShiftX(-loopLength_);
}
