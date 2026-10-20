#include "lanes/RoadLane.h"
#include "entities/Car.h"
#include "entities/Frog.h"
#include "Config.h"
#include "Theme.h"
#include <cmath>

namespace {

    const Color kPalette[] = { RED, ORANGE, YELLOW, SKYBLUE, PINK, WHITE };

    Color RandomCarColor() {
        return kPalette[GetRandomValue(0, static_cast<int>(std::size(kPalette)) - 1)];
    }

    struct CarPlan {
        std::vector<int>   variants;
        std::vector<float> widths;
        float totalWidth = 0.0f;
        float maxWidth = 0.0f;
    };

    CarPlan PickCars(int count) {
        CarPlan plan;
        for (int i = 0; i < count; ++i) {
            const int variant = GetRandomValue(0, Car::VariantCount - 1);
            const float width = Car::WidthFor(variant);
            plan.variants.push_back(variant);
            plan.widths.push_back(width);
            plan.totalWidth += width;
            plan.maxWidth = std::max(plan.maxWidth, width);
        }
        return plan;
    }

    float MinLoopForGaps(const CarPlan& plan) {
        return plan.totalWidth + static_cast<float>(plan.widths.size()) * Config::MinCarGap;
    }

    float LoopLengthFor(const CarPlan& plan) {
        const float offscreen = static_cast<float>(Config::ScreenW) + plan.maxWidth;
        return std::max(offscreen, MinLoopForGaps(plan));
    }

    std::vector<float> SpreadGaps(const CarPlan& plan, float loopLength) {
        const std::size_t n = plan.widths.size();
        const float slack = loopLength - MinLoopForGaps(plan);

        std::vector<float> shares(n);
        float shareSum = 0.0f;
        for (float& s : shares) {
            s = 0.5f + static_cast<float>(GetRandomValue(0, 100)) / 100.0f;
            shareSum += s;
        }

        std::vector<float> gaps(n);
        for (std::size_t i = 0; i < n; ++i) {
            gaps[i] = Config::MinCarGap + slack * shares[i] / shareSum;
        }
        return gaps;
    }

    std::vector<float> PlaceCars(const CarPlan& plan, const std::vector<float>& gaps, float loopLength) {
        float cursor = static_cast<float>(GetRandomValue(0, static_cast<int>(loopLength) - 1));

        std::vector<float> xs;
        for (std::size_t i = 0; i < plan.widths.size(); ++i) {
            xs.push_back(std::fmod(cursor + plan.maxWidth, loopLength) - plan.maxWidth);
            cursor += plan.widths[i] + gaps[i];
        }
        return xs;
    }
} // namespace

RoadLane::RoadLane(int row, float speed, int carCount) : Lane(row) {
    const CarPlan plan = PickCars(carCount);
    loopLength_ = LoopLengthFor(plan);
    const std::vector<float> gaps = SpreadGaps(plan, loopLength_);
    const std::vector<float> xs = PlaceCars(plan, gaps, loopLength_);

    for (std::size_t i = 0; i < xs.size(); ++i) {
        Add(std::make_unique<Car>(xs[i], row, plan.variants[i], speed, RandomCarColor()));
    }
}

LaneOutcome RoadLane::Resolve(Frog& frog, float) const {
    const Rectangle box = frog.HitBox();
    for (const auto& e : entities_) {
        if (CheckCollisionRecs(box, e->Bounds())) 
            return LaneOutcome::Killed;
    }
    return LaneOutcome::Safe;
}

void RoadLane::DrawBackground() const {
    DrawRectangle(0, row_ * Config::Cell, Config::ScreenW, Config::Cell, Theme::Road);
}

void RoadLane::Wrap(Entity& e) const {
    const Rectangle& b = e.Bounds();
    // Every car jumps by the same amount, so the gaps between them never change.
    if (e.Speed() > 0.0f && b.x > Config::ScreenW)          
        e.ShiftX(-loopLength_);
    else if (e.Speed() < 0.0f && b.x + b.width < 0.0f)      
        e.ShiftX(loopLength_);
}
