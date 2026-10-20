#pragma once
#include "core/CatalogCheck.h"

enum class SoundId { Hop, Hit, Splash, Goal, GameOver, Count };

struct SoundDef {
    SoundId id;
    const char* path;   // missing files are skipped safely at load time
    int voices;         // simultaneous copies (rapid hops overlap)
};

// The single source of truth for sounds. One row per SoundId.
inline constexpr SoundDef kSoundCatalog[] = {
    { SoundId::Hop,      "resources/Sounds/frogger_hop.wav",    4 },
    { SoundId::Hit,      "resources/Sounds/frogger_plunk.wav",  2 },
    { SoundId::Splash,   "resources/Sounds/frogger_squash.wav", 2 },
    { SoundId::Goal,     "resources/Sounds/goal.wav",           2 },
    { SoundId::GameOver, "resources/Sounds/Game_Over.mp3",      1 },
};

static_assert(CatalogMatchesEnum(kSoundCatalog, SoundId::Count),
    "kSoundCatalog must have exactly one row per SoundId, in the same order");