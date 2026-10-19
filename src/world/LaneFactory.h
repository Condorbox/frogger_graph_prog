#pragma once
#include "lanes/Lane.h"
#include <memory>
#include <vector>

// Factory: builds every lane of a level (rows RiverFirstRow..StartRow, in order).
class LaneFactory {
public:
    static std::vector<std::unique_ptr<Lane>> BuildLevel(int level);
};
