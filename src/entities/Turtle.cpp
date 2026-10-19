#include "entities/Turtle.h"
#include "core/ResourceManager.h"
#include <algorithm>

Turtle::Turtle(float x, int row, float speed)
    : Entity(Rectangle{ x,
                        static_cast<float>(row * Config::Cell) + (Config::Cell - Size) * 0.5f,
                        Size, Size },
        speed) {}

void Turtle::Draw() const {
    const ResourceManager& res = ResourceManager::Instance();

    if (res.Has(TextureId::Turtle)) {
        const Texture2D& t = res.Get(TextureId::Turtle);
        // Fit inside the bounds, keeping the sprite's aspect ratio.
        const float scale = std::min(bounds_.width / static_cast<float>(t.width),
            bounds_.height / static_cast<float>(t.height));
        const float w = static_cast<float>(t.width) * scale;
        const float h = static_cast<float>(t.height) * scale;
        const float cx = bounds_.x + bounds_.width * 0.5f;
        const float cy = bounds_.y + bounds_.height * 0.5f;
        DrawTexturePro(t,
            Rectangle{ 0.0f, 0.0f, static_cast<float>(t.width), static_cast<float>(t.height) },
            Rectangle{ cx - w * 0.5f, cy - h * 0.5f, w, h },
            Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
        return;
    }

    // Fallback: red shell with four green legs.
    const float cx = bounds_.x + bounds_.width * 0.5f;
    const float cy = bounds_.y + bounds_.height * 0.5f;
    const float r = bounds_.width * 0.5f;
    for (int sx = -1; sx <= 1; sx += 2) {
        for (int sy = -1; sy <= 1; sy += 2) {
            DrawCircle(static_cast<int>(cx + sx * r * 0.75f), static_cast<int>(cy + sy * r * 0.75f),
                r * 0.35f, GREEN);
        }
    }
    DrawCircle(static_cast<int>(cx), static_cast<int>(cy), r * 0.8f, RED);
    DrawCircle(static_cast<int>(cx), static_cast<int>(cy), r * 0.4f, MAROON);
}