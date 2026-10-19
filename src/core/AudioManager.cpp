#include "core/AudioManager.h"
#include "Config.h"

AudioManager& AudioManager::Instance() {
    static AudioManager instance;
    return instance;
}

void AudioManager::Init() {
    InitAudioDevice();
    deviceReady_ = true;

    // Order must match the SoundId enum.
    const char* paths[] = {
        Config::Paths::SoundHop, Config::Paths::SoundHit, Config::Paths::SoundSplash,
        Config::Paths::SoundGoal, Config::Paths::SoundGameOver
    };
    for (std::size_t i = 0; i < sounds_.size(); ++i) {
        if (FileExists(paths[i])) {
            sounds_[i].sound = LoadSound(paths[i]);
            sounds_[i].loaded = true;
        }
    }
    if (FileExists(Config::Paths::MusicTrack)) {
        music_ = LoadMusicStream(Config::Paths::MusicTrack);
        musicLoaded_ = true;
        SetMusicVolume(music_, 0.4f);
    }
}

void AudioManager::Shutdown() {
    for (SoundSlot& s : sounds_) {
        if (s.loaded) UnloadSound(s.sound);
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

void AudioManager::Play(SoundId id) const {
    const SoundSlot& s = sounds_[static_cast<std::size_t>(id)];
    if (s.loaded) PlaySound(s.sound);
}

void AudioManager::StartMusic() { if (musicLoaded_) PlayMusicStream(music_); }
void AudioManager::StopMusic()  { if (musicLoaded_) StopMusicStream(music_); }
