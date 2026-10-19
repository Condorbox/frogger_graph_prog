#pragma once
#include "core/GameState.h"
#include <memory>
#include <utility>

// Application object: owns the window and drives the state machine.
class Game {
public:
    Game();
    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void Run();

    // Requests a state change. It is applied at the end of the current frame,
    // so a state can safely ask to be replaced from inside its own Update().
    template <typename T, typename... Args>
    void ChangeState(Args&&... args) {
        pending_ = std::make_unique<T>(*this, std::forward<Args>(args)...);
    }

private:
    void ApplyPendingState();

    std::unique_ptr<GameState> current_;
    std::unique_ptr<GameState> pending_;
};
