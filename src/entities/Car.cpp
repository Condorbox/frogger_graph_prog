#include "entities/Car.h"
#include "core/ResourceManager.h"

namespace {
    constexpr TextureId kTextures[Car::VariantCount] = {
        TextureId::Truck1, TextureId::Truck2, TextureId::Truck3, TextureId::Truck4, TextureId::Truck5
    };

    // Which way each sprite's art points. Sprites are flipped when the lane
    // direction doesn't match. If a car looks like it drives backwards, flip its entry.
    constexpr bool kFacesRight[Car::VariantCount] = { false, false, false, false, false };

    // Width in cells when the PNG is missing.
    constexpr float kFallbackCells[Car::VariantCount] = { 1.0f, 1.0f, 1.0f, 1.0f, 2.0f };
}  // namespace


Car::Car(float x, int row, int variant, float speed, Color color)
    : Entity(Rectangle{ x,
                        static_cast<float>(row * Config::Cell) + (Config::Cell - Height) * 0.5f,
                        WidthFor(variant), Height },
        speed),
    variant_(variant), color_(color) {}

float Car::WidthFor(int variant) {
    const ResourceManager& res = ResourceManager::Instance();
    const TextureId id = kTextures[variant];
    if (res.Has(id)) {
        const Texture2D& t = res.Get(id);
        return static_cast<float>(t.width) * (Height / static_cast<float>(t.height));
    }
    return kFallbackCells[variant] * static_cast<float>(Config::Cell);
}

void Car::Draw() const {
    const ResourceManager& res = ResourceManager::Instance();
    const TextureId id = kTextures[variant_];

    if (res.Has(id)) {
        const Texture2D& t = res.Get(id);
        const bool movingRight = speed_ > 0.0f;
        const float flip = (movingRight == kFacesRight[variant_]) ? 1.0f : -1.0f;   // negative width mirrors
        DrawTexturePro(t,
            Rectangle{ 0.0f, 0.0f, flip * static_cast<float>(t.width), static_cast<float>(t.height) },
            bounds_, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
    }
    else {
        DrawRectangleRounded(bounds_, 0.3f, 6, color_);
    }
}
