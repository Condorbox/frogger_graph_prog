#include "lanes/SafeLane.h"
#include "Config.h"

void SafeLane::DrawBackground() const {
    DrawRectangle(0, row_ * Config::Cell, Config::ScreenW, Config::Cell, color_);
}
