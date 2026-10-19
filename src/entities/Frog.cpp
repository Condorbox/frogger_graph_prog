#include "entities/Frog.h"
#include "Config.h"
#include "core/ResourceManager.h"
#include <algorithm>
#include <cmath>

namespace {
constexpr float MaxX = static_cast<float>(Config::ScreenW - Config::Cell);

    // Direction -> texture. Swap Up/Down here if your F/D naming is reversed.
    TextureId SpriteFor(Direction dir, bool jumping) {
        switch (dir) {
            case Direction::Up:    return jumping ? TextureId::PlayerJumpUp : TextureId::PlayerUp;
            case Direction::Down:  return jumping ? TextureId::PlayerJumpDown : TextureId::PlayerDown;
            case Direction::Left:  return jumping ? TextureId::PlayerJumpLeft : TextureId::PlayerLeft;
            case Direction::Right: return jumping ? TextureId::PlayerJumpRight : TextureId::PlayerRight;
        }
        return TextureId::PlayerUp;
    }
} // namespace

void Frog::Reset() {
    x_ = static_cast<float>((Config::Cols / 2) * Config::Cell);
    row_ = Config::StartRow;
    facing_ = Direction::Up;
    hopTimer_ = 0.0f;
}

bool Frog::Hop(Direction dir) {
    facing_ = dir;   // turn even if the hop itself is blocked
    bool moved = false;

    switch (dir) {
    case Direction::Up:
        if (row_ > Config::GoalRow) { --row_; moved = true; }
        break;
    case Direction::Down:
        if (row_ < Config::StartRow) { ++row_; moved = true; }
        break;
    case Direction::Left:
        if (x_ > 0.0f) { x_ = std::max(0.0f, x_ - Config::Cell); moved = true; }
        break;
    case Direction::Right:
        if (x_ < MaxX) { x_ = std::min(MaxX, x_ + Config::Cell); moved = true; }
        break;
    }

    if (moved) hopTimer_ = Config::HopDuration;
    return moved;
}

void Frog::SnapToGrid() {
    x_ = std::round(x_ / Config::Cell) * Config::Cell;
    x_ = std::clamp(x_, 0.0f, MaxX);
}

float Frog::CenterX() const {
    return x_ + Config::Cell * 0.5f;
}

void Frog::Update(float dt) {
    hopTimer_ = std::max(0.0f, hopTimer_ - dt);
}

Rectangle Frog::HitBox() const {
    return Rectangle{ x_ + 10.0f, static_cast<float>(row_ * Config::Cell + 10), 30.0f, 30.0f };
}

void Frog::Draw() const {
    const bool jumping = hopTimer_ > 0.0f;
    float lift = 0.0f;
    if (jumping) {
        const float progress = 1.0f - hopTimer_ / Config::HopDuration;   // 0 -> 1
        lift = std::sin(progress * PI) * Config::HopLift;
    }
    DrawShape(CenterX(), row_ * Config::Cell + Config::Cell * 0.5f - lift, 17.0f, facing_, jumping);
}


void Frog::DrawShape(float cx, float cy, float r, Direction facing, bool jumping) {
    const ResourceManager& res = ResourceManager::Instance();
    const TextureId id = SpriteFor(facing, jumping);

    if (res.Has(id)) {
        const Texture2D& t = res.Get(id);
        const float box = r * 2.0f * Config::FrogSpriteScale;
        const float scale = std::min(box / static_cast<float>(t.width), box / static_cast<float>(t.height));
        const float w = static_cast<float>(t.width) * scale;
        const float h = static_cast<float>(t.height) * scale;
        DrawTexturePro(t,
            Rectangle{ 0.0f, 0.0f, static_cast<float>(t.width), static_cast<float>(t.height) },
            Rectangle{ cx - w * 0.5f, cy - h * 0.5f, w, h },
            Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
        return;
    }

    // Fallback: the original circle frog.
    const int x = static_cast<int>(cx), y = static_cast<int>(cy);
    const int ex = static_cast<int>(r * 0.5f), ey = static_cast<int>(r * 0.6f);
    DrawCircle(x, y, r, LIME);
    DrawCircle(x - ex, y - ey, r * 0.3f, WHITE);
    DrawCircle(x + ex, y - ey, r * 0.3f, WHITE);
    DrawCircle(x - ex, y - ey, r * 0.12f, BLACK);
    DrawCircle(x + ex, y - ey, r * 0.12f, BLACK);
}
