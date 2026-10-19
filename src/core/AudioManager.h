#pragma once
#include "raylib.h"
#include <array>
#include <cstddef>
#include <vector>

enum class SoundId { Hop, Hit, Splash, Goal, GameOver, Count };

// Singleton: one audio device, one set of sounds, one music stream.
class AudioManager {
public:
    static AudioManager& Instance();

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    void Init();       // opens the audio device and loads files (missing ones are skipped)
    void Shutdown();
    void Update();     // call every frame to feed the music stream

    void Play(SoundId id);
    void Stop(SoundId id);
    void StopAll(); // silences every sound effect (music is not affected)
    void StartMusic();
    void StopMusic();

private:
    AudioManager() = default;

    struct SoundSlot {
        std::vector<Sound> voices;
        bool loaded = false;
    };
    
    std::array<SoundSlot, static_cast<std::size_t>(SoundId::Count)> sounds_{};
    Music music_{};
    bool musicLoaded_ = false;
    bool deviceReady_ = false;
};
