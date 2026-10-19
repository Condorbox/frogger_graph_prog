#include "core/Game.h"
#include "core/AudioManager.h"
#include "core/ResourceManager.h"
#include "states/TitleState.h"
#include "Config.h"
#include "raylib.h"
#include <ctime>

Game::Game() {
    InitWindow(Config::ScreenW, Config::ScreenH, Config::WindowTitle);
    SetTargetFPS(Config::TargetFps);
    SetRandomSeed(static_cast<unsigned int>(std::time(nullptr)));

    ResourceManager::Instance().LoadAll();
    AudioManager::Instance().Init();

    current_ = std::make_unique<TitleState>(*this);
    current_->OnEnter();
}

Game::~Game() {
    pending_.reset();
    current_.reset();
    AudioManager::Instance().Shutdown();
    ResourceManager::Instance().UnloadAll();
    CloseWindow();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        AudioManager::Instance().Update();

        current_->Update(GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);
        current_->Draw();
        EndDrawing();

        ApplyPendingState();
    }
}

void Game::ApplyPendingState() {
    if (!pending_) return;
    current_->OnExit();
    current_ = std::move(pending_);
    current_->OnEnter();
}
