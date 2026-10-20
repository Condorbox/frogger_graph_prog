#include "lanes/SafeLane.h"
#include "world/TileUtils.h"
#include "Config.h"

void SafeLane::DrawBackground() const {
    DrawTiledRow(row_, TextureId::Floor, color_);
}
