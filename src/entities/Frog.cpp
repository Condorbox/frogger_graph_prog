#include "entities/Frog.h"
#include "Config.h"
#include <algorithm>
#include <cmath>

namespace {
constexpr float MaxX = static_cast<float>(Config::ScreenW - Config::Cell);
}

void Frog::Reset() {
    x_ = static_cast<float>((Config::Cols / 2) * Config::Cell);
    row_ = Config::StartRow;
}

bool Frog::Hop(Direction dir) {
    switch (dir) {
        case Direction::Up:
            if (row_ <= Config::GoalRow) return false;
            --row_;
            return true;
        case Direction::Down:
            if (row_ >= Config::StartRow) return false;
            ++row_;
            return true;
        case Direction::Left:
            if (x_ <= 0.0f) return false;
            x_ = std::max(0.0f, x_ - Config::Cell);
            return true;
        case Direction::Right:
            if (x_ >= MaxX) return false;
            x_ = std::min(MaxX, x_ + Config::Cell);
            return true;
    }
    return false;
}

void Frog::SnapToGrid() {
    x_ = std::round(x_ / Config::Cell) * Config::Cell;
    x_ = std::clamp(x_, 0.0f, MaxX);
}

float Frog::CenterX() const {
    return x_ + Config::Cell * 0.5f;
}

Rectangle Frog::HitBox() const {
    return Rectangle{ x_ + 10.0f, static_cast<float>(row_ * Config::Cell + 10), 30.0f, 30.0f };
}

void Frog::Draw() const {
    DrawShape(CenterX(), row_ * Config::Cell + Config::Cell * 0.5f, 17.0f);
}

void Frog::DrawShape(float cx, float cy, float r) {
    const int x = static_cast<int>(cx), y = static_cast<int>(cy);
    const int ex = static_cast<int>(r * 0.5f), ey = static_cast<int>(r * 0.6f);
    DrawCircle(x, y, r, LIME);
    DrawCircle(x - ex, y - ey, r * 0.3f, WHITE);
    DrawCircle(x + ex, y - ey, r * 0.3f, WHITE);
    DrawCircle(x - ex, y - ey, r * 0.12f, BLACK);
    DrawCircle(x + ex, y - ey, r * 0.12f, BLACK);
}
