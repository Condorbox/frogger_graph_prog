#include "world/GoalRow.h"
#include "entities/Frog.h"
#include "world/TileUtils.h"
#include "Theme.h"
#include <algorithm>
#include <cmath>

int GoalRow::SlotIndexAt(const Frog& frog) const {
    const int col = static_cast<int>(std::round(frog.X() / Config::Cell));
    for (int i = 0; i < Config::NumSlots; ++i) {
        if (Config::SlotColumn(i) == col) return i;
    }
    return -1;
}

bool GoalRow::CanEnter(const Frog& frog) const {
    const int idx = SlotIndexAt(frog);
    return idx >= 0 && !filled_[static_cast<std::size_t>(idx)];
}

void GoalRow::Occupy(const Frog& frog) {
    const int idx = SlotIndexAt(frog);
    if (idx >= 0) filled_[static_cast<std::size_t>(idx)] = true;
}

bool GoalRow::AllFilled() const {
    return std::all_of(filled_.begin(), filled_.end(), [](bool f) { return f; });
}

void GoalRow::Draw() const {
    DrawTiledRow(Config::GoalRow, TextureId::Bush, Theme::Grass);
    for (int i = 0; i < Config::NumSlots; ++i) {
        const int x = Config::SlotColumn(i) * Config::Cell;
        DrawRectangle(x, Config::GoalRow * Config::Cell, Config::Cell, Config::Cell, Theme::Water);
        if (filled_[static_cast<std::size_t>(i)]) {
            Frog::DrawShape(x + Config::Cell * 0.5f, Config::GoalRow * Config::Cell + Config::Cell * 0.5f, 17.0f);
        }
    }
}
