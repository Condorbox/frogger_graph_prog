#include "entities/Turtle.h"
#include "core/ResourceManager.h"
#include <algorithm>

namespace {
    float RandomRange(float lo, float hi) {
        return lo + (hi - lo) * static_cast<float>(GetRandomValue(0, 1000)) / 1000.0f;
    }

    // Draws a texture centered in `bounds`, keeping its aspect ratio.
    void DrawFitted(const Texture2D& t, const Rectangle& bounds, Color tint = WHITE) {
        const float scale = std::min(bounds.width / static_cast<float>(t.width),
            bounds.height / static_cast<float>(t.height));
        const float w = static_cast<float>(t.width) * scale;
        const float h = static_cast<float>(t.height) * scale;
        const float cx = bounds.x + bounds.width * 0.5f;
        const float cy = bounds.y + bounds.height * 0.5f;
        DrawTexturePro(t,
            Rectangle{ 0.0f, 0.0f, static_cast<float>(t.width), static_cast<float>(t.height) },
            Rectangle{ cx - w * 0.5f, cy - h * 0.5f, w, h },
            Vector2{ 0.0f, 0.0f }, 0.0f, tint);
    }
}  // namespace

Turtle::Turtle(float x, int row, float speed)
    : Entity(Rectangle{ x,
                        static_cast<float>(row * Config::Cell) + (Config::Cell - Size) * 0.5f,
                        Size, Size },
        speed) {
    // Random starting state so turtles are not in sync.
    Enter(GetRandomValue(0, 1) == 0 ? TurtleState::Disabled : TurtleState::Enabled);
}

void Turtle::Enter(TurtleState state) {
    state_ = state;
    timer_ = (state == TurtleState::Enabled)
        ? RandomRange(Config::TurtleDeadlyMin, Config::TurtleDeadlyMax)
        : RandomRange(Config::TurtleHiddenMin, Config::TurtleHiddenMax);
}

void Turtle::Update(float dt) {
    Entity::Update(dt);   // keep moving
    timer_ -= dt;
    if (timer_ <= 0.0f) {
        Enter(state_ == TurtleState::Enabled ? TurtleState::Disabled : TurtleState::Enabled);
    }
}

void Turtle::Draw() const {
    if (state_ == TurtleState::Enabled) {
        DrawEnabledLook(1.0f);
        return;
    }

    if (IsWarning()) {
        // Flash the surfaced look, translucent so it reads as "about to", not "deadly now".
        const bool flashOn = (static_cast<int>(timer_ / Config::TurtleBlinkInterval) % 2) == 0;
        if (flashOn) {
            DrawEnabledLook(Config::TurtleGhostAlpha);
            return;
        }
    }

    DrawDisabledLook();
}

void Turtle::DrawEnabledLook(float alpha) const {
    const ResourceManager& res = ResourceManager::Instance();

    if (res.Has(TextureId::TurtleEnabled)) {
        DrawFitted(res.Get(TextureId::TurtleEnabled), bounds_, Fade(WHITE, alpha));
        return;
    }

    // Fallback: red shell with four green legs.
    const float cx = bounds_.x + bounds_.width * 0.5f;
    const float cy = bounds_.y + bounds_.height * 0.5f;
    const float r = bounds_.width * 0.5f;
    for (int sx = -1; sx <= 1; sx += 2) {
        for (int sy = -1; sy <= 1; sy += 2) {
            DrawCircle(static_cast<int>(cx + sx * r * 0.75f), static_cast<int>(cy + sy * r * 0.75f),
                r * 0.35f, Fade(GREEN, alpha));
        }
    }
    DrawCircle(static_cast<int>(cx), static_cast<int>(cy), r * 0.8f, Fade(RED, alpha));
    DrawCircle(static_cast<int>(cx), static_cast<int>(cy), r * 0.4f, Fade(MAROON, alpha));
}

void Turtle::DrawDisabledLook() const {
    const ResourceManager& res = ResourceManager::Instance();

    if (res.Has(TextureId::TurtleDisabled)) {
        DrawFitted(res.Get(TextureId::TurtleDisabled), bounds_);
        return;
    }

    // Fallback: faint ripples where the turtle is lurking.
    const float cx = bounds_.x + bounds_.width * 0.5f;
    const float cy = bounds_.y + bounds_.height * 0.5f;
    const float r = bounds_.width * 0.5f;
    const Color c = Fade(WHITE, 0.35f);
    DrawEllipseLines(static_cast<int>(cx), static_cast<int>(cy), r * 0.9f, r * 0.5f, c);
    DrawEllipseLines(static_cast<int>(cx), static_cast<int>(cy), r * 0.5f, r * 0.28f, c);
}