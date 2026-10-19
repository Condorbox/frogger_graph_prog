#pragma once

class GameSession;

// Bottom bar: lives, timer, level and score. Read-only view of a GameSession.
class Hud {
public:
    void Draw(const GameSession& session) const;
};
