#include "core/ResourceManager.h"
#include "Config.h"

ResourceManager& ResourceManager::Instance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::LoadAll() {
    const char* paths[] = { Config::Paths::Log1U, Config::Paths::Log2U, Config::Paths::Log4U };
    for (std::size_t i = 0; i < textures_.size(); ++i) {
        if (FileExists(paths[i])) {
            textures_[i].texture = LoadTexture(paths[i]);
            textures_[i].loaded = (textures_[i].texture.id != 0);
        }
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
