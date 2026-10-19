#include "states/PlayingState.h"
#include "core/AudioManager.h"
#include "core/Game.h"
#include "states/GameOverState.h"
#include "raylib.h"

void PlayingState::OnEnter() {
    session_.Reset();
    world_.StartLevel(1);
    AudioManager::Instance().StartMusic();
}

void PlayingState::Update(float dt) {
    session_.Tick(dt);

    HandleInput();
    world_.Update(dt);
    ProcessWorldEvents();

    if (!session_.IsGameOver() && session_.TimeExpired()) {
        session_.RestartTimer();
        world_.ResetFrog();
        LoseLife(false);
    }

    if (session_.IsGameOver()) {
        auto& audio = AudioManager::Instance();
        audio.StopMusic();
        audio.Play(SoundId::GameOver);
        game_.ChangeState<GameOverState>(session_.Score());
    }
}

void PlayingState::Draw() const {
    world_.Draw();
    hud_.Draw(session_);
}

void PlayingState::HandleInput() {
    if (IsKeyPressed(KEY_UP)    || IsKeyPressed(KEY_W)) world_.HopFrog(Direction::Up);
    if (IsKeyPressed(KEY_DOWN)  || IsKeyPressed(KEY_S)) world_.HopFrog(Direction::Down);
    if (IsKeyPressed(KEY_LEFT)  || IsKeyPressed(KEY_A)) world_.HopFrog(Direction::Left);
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) world_.HopFrog(Direction::Right);
}

void PlayingState::ProcessWorldEvents() {
    auto& audio = AudioManager::Instance();

    for (WorldEvent ev : world_.ConsumeEvents()) {
        switch (ev) {
            case WorldEvent::FrogHopped:
                audio.Play(SoundId::Hop);
                break;
            case WorldEvent::SlotFilled:
                session_.AddScore(Config::SlotPoints);
                audio.Play(SoundId::Goal);
                break;
            case WorldEvent::LevelCleared:
                session_.CompleteLevel();
                world_.StartLevel(session_.Level());
                break;
            case WorldEvent::FrogKilled:
                LoseLife(false);
                break;
            case WorldEvent::FrogDrowned:
                LoseLife(true);
                break;
        }
        if (session_.IsGameOver()) break;
    }
}

void PlayingState::LoseLife(bool drowned) {
    AudioManager::Instance().Play(drowned ? SoundId::Splash : SoundId::Hit);
    session_.LoseLife();
}
