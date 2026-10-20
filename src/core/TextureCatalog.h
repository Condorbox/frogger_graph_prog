#pragma once
#include "core/CatalogCheck.h"

enum class TextureId {
    Log1U, Log2U, Log4U,
    PlayerUp, PlayerDown, PlayerLeft, PlayerRight,
    PlayerJumpUp, PlayerJumpDown, PlayerJumpLeft, PlayerJumpRight,
    TurtleEnabled, TurtleDisabled,
    Truck1, Truck2, Truck3, Truck4, Truck5,
    Floor, Bush, Home,
    Count
};

struct TextureDef {
    TextureId id;
    const char* path;   // missing files are skipped safely at load time
};

// The single source of truth for textures. One row per TextureId.
inline constexpr TextureDef kTextureCatalog[] = {
    { TextureId::Log1U,           "resources/Game/Enemies/Log1U.png" },
    { TextureId::Log2U,           "resources/Game/Enemies/Log2U.png" },
    { TextureId::Log4U,           "resources/Game/Enemies/Log4U.png" },
    { TextureId::PlayerUp,        "resources/Game/Player_F.png" },
    { TextureId::PlayerDown,      "resources/Game/Player_D.png" },
    { TextureId::PlayerLeft,      "resources/Game/Player_L.png" },
    { TextureId::PlayerRight,     "resources/Game/Player_R.png" },
    { TextureId::PlayerJumpUp,    "resources/Game/PlayerJump_F.png" },
    { TextureId::PlayerJumpDown,  "resources/Game/PlayerJump_D.png" },
    { TextureId::PlayerJumpLeft,  "resources/Game/PlayerJump_L.png" },
    { TextureId::PlayerJumpRight, "resources/Game/PlayerJump_R.png" },
    { TextureId::TurtleEnabled,   "resources/Game/Enemies/TurtleEnabled.png" },
    { TextureId::TurtleDisabled,  "resources/Game/Enemies/TurtleDisabled.png" },
    { TextureId::Truck1,          "resources/Game/Enemies/Truck1.png" },
    { TextureId::Truck2,          "resources/Game/Enemies/Truck2.png" },
    { TextureId::Truck3,          "resources/Game/Enemies/Truck3.png" },
    { TextureId::Truck4,          "resources/Game/Enemies/Truck4.png" },
    { TextureId::Truck5,          "resources/Game/Enemies/Truck5.png" },
    { TextureId::Floor,           "resources/Game/Floor.png" },
    { TextureId::Bush,            "resources/Game/Bush.png" },
    { TextureId::Home,            "resources/Game/Home.png" },
};

static_assert(CatalogMatchesEnum(kTextureCatalog, TextureId::Count),
    "kTextureCatalog must have exactly one row per TextureId, in the same order");