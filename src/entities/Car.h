#pragma once
#include "entities/Entity.h"
#include "Config.h"

class Car final : public Entity {
public:
    static constexpr int   VariantCount = 5;
    static constexpr float Height = static_cast<float>(Config::Cell - 10);

    Car(float x, int row, int variant, float speed, Color color);
    void Draw() const override;

    static float WidthFor(int variant);

private:
    int variant_;
    Color color_;   // only used by the fallback 
};
