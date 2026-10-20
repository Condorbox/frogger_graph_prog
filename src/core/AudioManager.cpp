#include "core/AudioManager.h"
#include "Config.h"

AudioManager& AudioManager::Instance() {
    static AudioManager instance;
    return instance;
}

void AudioManager::Init() {
    InitAudioDevice();
    deviceReady_ = true;

    for (const SoundDef& def : kSoundCatalog) {
        if (!FileExists(def.path)) continue;

        const Sound source = LoadSound(def.path);
        if (source.frameCount == 0) continue;   // failed to load

        SoundSlot& slot = sounds_[static_cast<std::size_t>(def.id)];
        slot.voices.push_back(source);
        for (int v = 1; v < def.voices; ++v) {
            slot.voices.push_back(LoadSoundAlias(source));
        }
        slot.loaded = true;
    }

    if (FileExists(Config::Paths::MusicTrack)) {
        music_ = LoadMusicStream(Config::Paths::MusicTrack);
        musicLoaded_ = true;
        SetMusicVolume(music_, 0.4f);
    }
}

void AudioManager::Shutdown() {
    for (SoundSlot& s : sounds_) {
        // Aliases must be unloaded before the sound that owns the data.
        for (std::size_t v = 1; v < s.voices.size(); ++v) UnloadSoundAlias(s.voices[v]);
        if (!s.voices.empty()) UnloadSound(s.voices[0]);
        s.voices.clear();
        s.loaded = false;
    }
    if (musicLoaded_) UnloadMusicStream(music_);
    musicLoaded_ = false;
    if (deviceReady_) CloseAudioDevice();
    deviceReady_ = false;
}

void AudioManager::Update() {
    if (musicLoaded_) UpdateMusicStream(music_);
}

void AudioManager::Play(SoundId id) {
    SoundSlot& s = sounds_[static_cast<std::size_t>(id)];
    if (!s.loaded) return;
    for (const Sound& voice : s.voices) {
        if (!IsSoundPlaying(voice)) {
            PlaySound(voice);
            return;
        }
    }
    // Every voice is busy: skip instead of restarting one.
}

void AudioManager::Stop(SoundId id) {
    SoundSlot& s = sounds_[static_cast<std::size_t>(id)];
    if (!s.loaded) return;
    for (const Sound& voice : s.voices) StopSound(voice);
}

void AudioManager::StopAll() {
    for (SoundSlot& s : sounds_) {
        for (const Sound& voice : s.voices) StopSound(voice);
    }
}

void AudioManager::StartMusic() { if (musicLoaded_) PlayMusicStream(music_); }
void AudioManager::StopMusic()  { if (musicLoaded_) StopMusicStream(music_); }
