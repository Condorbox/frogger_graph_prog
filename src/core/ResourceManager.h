#pragma once
#include "raylib.h"
#include <array>
#include <cstddef>

enum class TextureId { 
    Log1U, Log2U, Log4U, PlayerUp, PlayerDown, PlayerLeft, PlayerRight,
    PlayerJumpUp, PlayerJumpDown, PlayerJumpLeft, PlayerJumpRight, 
    Count };

// Singleton: one global owner of all textures.
// Needs an explicit LoadAll()/UnloadAll() because raylib requires the window
// to exist before loading and to still exist when unloading.
class ResourceManager {
public:
    static ResourceManager& Instance();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    void LoadAll();
    void UnloadAll();

    bool Has(TextureId id) const;                 // false if the file was missing
    const Texture2D& Get(TextureId id) const;     // only call when Has(id)

private:
    ResourceManager() = default;

    struct Slot {
        Texture2D texture{};
        bool loaded = false;
    };
    std::array<Slot, static_cast<std::size_t>(TextureId::Count)> textures_{};
};
