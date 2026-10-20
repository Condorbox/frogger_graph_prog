#include "core/ResourceManager.h"

ResourceManager& ResourceManager::Instance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::LoadAll() {
    for (const TextureDef& def : kTextureCatalog) {
        if (!FileExists(def.path)) continue;

        Slot& slot = textures_[static_cast<std::size_t>(def.id)];
        slot.texture = LoadTexture(def.path);
        slot.loaded = (slot.texture.id != 0);
    }
}

void ResourceManager::UnloadAll() {
    for (Slot& slot : textures_) {
        if (slot.loaded) UnloadTexture(slot.texture);
        slot.loaded = false;
    }
}

bool ResourceManager::Has(TextureId id) const {
    return textures_[static_cast<std::size_t>(id)].loaded;
}

const Texture2D& ResourceManager::Get(TextureId id) const {
    return textures_[static_cast<std::size_t>(id)].texture;
}
