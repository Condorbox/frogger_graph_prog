#pragma once

enum class Direction { Up, Down, Left, Right };

// What a lane does to the frog standing on it.
enum class LaneOutcome { Safe, Killed, Drowned };

// Things that happened in the world this frame (consumed by the game state).
enum class WorldEvent { FrogHopped, FrogKilled, FrogDrowned, SlotFilled, LevelCleared };
