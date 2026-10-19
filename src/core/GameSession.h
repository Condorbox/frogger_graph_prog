#pragma once
#include "Config.h"
#include <algorithm>

// Rules/score data for one run: lives, score, level, level timer.
// Knows nothing about drawing, input or the world layout.
class GameSession {
public:
    GameSession() { Reset(); }

    void Reset() {
        lives_ = Config::MaxLives;
        score_ = 0;
        level_ = 1;
        timer_ = 0.0f;
    }

    void Tick(float dt)       { timer_ += dt; }
    void RestartTimer()       { timer_ = 0.0f; }
    bool TimeExpired() const  { return timer_ > Config::LevelTime; }

    void LoseLife()           { --lives_; }
    bool IsGameOver() const   { return lives_ <= 0; }
    void AddScore(int points) { score_ += points; }

    void CompleteLevel() {
        const int secondsLeft = static_cast<int>(std::max(0.0f, Config::LevelTime - timer_));
        score_ += Config::LevelBonus + secondsLeft * Config::TimeBonusPerSecond;
        ++level_;
        timer_ = 0.0f;
    }

    int   Lives() const   { return lives_; }
    int   Score() const   { return score_; }
    int   Level() const   { return level_; }
    float Elapsed() const { return timer_; }
    float TimeLeftRatio() const { return std::max(0.0f, 1.0f - timer_ / Config::LevelTime); }

private:
    int lives_ = Config::MaxLives;
    int score_ = 0;
    int level_ = 1;
    float timer_ = 0.0f;
};
