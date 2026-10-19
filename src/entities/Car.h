#pragma once
#include "entities/Entity.h"

class Car final : public Entity {
public:
    Car(Rectangle bounds, float speed, Color color);
    void Draw() const override;

private:
    Color color_;
};
