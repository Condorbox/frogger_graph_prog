#pragma once
#include "raylib.h"
#include "world/WorldTypes.h"

// The player. Position is a pixel x (so a log can carry it between cells)
// and an integer row.
class Frog {
public:
    Frog() { Reset(); }

    void Reset();
    bool Hop(Direction dir);          // false if the hop is blocked by the screen edge
    void SnapToGrid();                // aligns x to the nearest cell
    void CarryBy(float dx) { x_ += dx; }
    void Update(float dt);            // advances the hop animation
    void Draw() const;

    float X() const { return x_; }
    int Row() const { return row_; }
    float CenterX() const;
    Rectangle HitBox() const;

    // Also used by the HUD (lives), goal slots and title screen.
    // Draws the sprite if loaded, otherwise the fallback circle frog.
    static void DrawShape(float cx, float cy, float radius,
        Direction facing = Direction::Up, bool jumping = false);

private:
    float x_ = 0.0f;
    int row_ = 0;
    Direction facing_ = Direction::Up;
    float hopTimer_ = 0.0f;        
};
