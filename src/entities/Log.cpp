#include "entities/Log.h"
#include "core/ResourceManager.h"

namespace {
TextureId TextureFor(LogType type) {
    switch (type) {
        case LogType::Log1U: return TextureId::Log1U;
        case LogType::Log2U: return TextureId::Log2U;
        case LogType::Log4U: return TextureId::Log4U;
    }
    return TextureId::Log1U;
}
}  // namespace

Log::Log(float x, int row, LogType type, float speed)
    : Entity(Rectangle{ x, static_cast<float>(row * Config::Cell + 4), WidthFor(type), Height }, speed),
      type_(type) {}

float Log::WidthFor(LogType type) {
    const ResourceManager& res = ResourceManager::Instance();
    const TextureId id = TextureFor(type);
    if (res.Has(id)) {
        const Texture2D& t = res.Get(id);
        return static_cast<float>(t.width) * (Height / static_cast<float>(t.height));
    }
    // Fallback widths when there is no texture.
    switch (type) {
        case LogType::Log1U: return 1.0f * Config::Cell;
        case LogType::Log2U: return 2.0f * Config::Cell;
        case LogType::Log4U: return 4.0f * Config::Cell;
    }
    return static_cast<float>(Config::Cell);
}

void Log::Draw() const {
    const ResourceManager& res = ResourceManager::Instance();
    const TextureId id = TextureFor(type_);
    if (res.Has(id)) {
        const Texture2D& t = res.Get(id);
        DrawTexturePro(t,
                       Rectangle{ 0.0f, 0.0f, static_cast<float>(t.width), static_cast<float>(t.height) },
                       bounds_, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
    } else {
        DrawRectangleRounded(bounds_, 0.4f, 6, DARKBROWN);
        const Rectangle inner{ bounds_.x + 2.0f, bounds_.y + 2.0f, bounds_.width - 4.0f, bounds_.height - 4.0f };
        DrawRectangleRounded(inner, 0.4f, 6, BROWN);
    }
}
