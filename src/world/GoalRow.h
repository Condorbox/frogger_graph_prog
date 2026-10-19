#pragma once
#include "Config.h"
#include <array>

class Frog;

// The top row: NumSlots exits the frog has to fill.
class GoalRow {
public:
    GoalRow() { Reset(); }

    void Reset() { filled_.fill(false); }
    bool CanEnter(const Frog& frog) const;   // frog is above a free slot
    void Occupy(const Frog& frog);
    bool AllFilled() const;
    void Draw() const;

private:
    int SlotIndexAt(const Frog& frog) const; // -1 if the frog is not above a slot
    std::array<bool, Config::NumSlots> filled_{};
};
