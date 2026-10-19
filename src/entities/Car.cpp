#include "entities/Car.h"

Car::Car(Rectangle bounds, float speed, Color color)
    : Entity(bounds, speed), color_(color) {}

void Car::Draw() const {
    DrawRectangleRounded(bounds_, 0.3f, 6, color_);
}
