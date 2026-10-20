#pragma once
#include "raylib.h"

// Base class for anything that moves horizontally at a constant speed.
class Entity {
public:
    Entity(Rectangle bounds, float speed) : bounds_(bounds), speed_(speed) {}
    virtual ~Entity() = default;

    virtual void Update(float dt) { bounds_.x += speed_ * dt; }
    virtual void Draw() const = 0;

    const Rectangle& Bounds() const { return bounds_; }
    float Speed() const { return speed_; }
    virtual bool IsDeadly() const { return false; }
    void SetX(float x) { bounds_.x = x; }
    void ShiftX(float dx) { bounds_.x += dx; }

protected:
    Rectangle bounds_;
    float speed_;
};
