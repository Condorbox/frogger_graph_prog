#pragma once

class Game;

// State pattern: each screen of the app is a GameState.
class GameState {
public:
    explicit GameState(Game& game) : game_(game) {}
    virtual ~GameState() = default;

    virtual void OnEnter() {}
    virtual void OnExit() {}
    virtual void Update(float dt) = 0;
    virtual void Draw() const = 0;

protected:
    Game& game_;
};
