#pragma once

// All tunable numbers and asset paths live here. No magic numbers elsewhere.
namespace Config {

inline constexpr const char* WindowTitle = "Frogger";
inline constexpr int TargetFps = 60;

// Grid
inline constexpr int Cell    = 50;
inline constexpr int Cols    = 16;
inline constexpr int Rows    = 12;
inline constexpr int ScreenW = Cell * Cols;   // 800
inline constexpr int ScreenH = Cell * Rows;   // 600

// Row layout (0 = top)
inline constexpr int GoalRow       = 0;
inline constexpr int RiverFirstRow = 1;
inline constexpr int RiverLastRow  = 3;
inline constexpr int MedianRow     = 4;
inline constexpr int RoadFirstRow  = 5;
inline constexpr int RoadLastRow   = 9;
inline constexpr int StartRow      = 10;
inline constexpr int HudRow        = 11;

// Rules
inline constexpr int   NumSlots            = 5;
inline constexpr int   MaxLives            = 3;
inline constexpr float LevelTime           = 60.0f;   // seconds to fill every exit
inline constexpr float SpeedGrowthPerLevel = 0.12f;
inline constexpr int   SlotPoints          = 100;
inline constexpr int   LevelBonus          = 500;
inline constexpr int   TimeBonusPerSecond  = 10;

constexpr bool IsRiverRow(int row) { return row >= RiverFirstRow && row <= RiverLastRow; }
constexpr bool IsRoadRow(int row)  { return row >= RoadFirstRow  && row <= RoadLastRow; }
constexpr int  SlotColumn(int i)   { return 1 + i * 3; }   // columns 1,4,7,10,13

// Asset paths (relative to the working directory). Missing files are skipped safely.
namespace Paths {
inline constexpr const char* Log1U       = "resources/Game/Enemies/Log1U.png";
inline constexpr const char* Log2U       = "resources/Game/Enemies/Log2U.png";
inline constexpr const char* Log4U       = "resources/Game/Enemies/Log4U.png";
inline constexpr const char* SoundHop      = "resources/Audio/hop.wav";
inline constexpr const char* SoundHit      = "resources/Audio/hit.wav";
inline constexpr const char* SoundSplash   = "resources/Audio/splash.wav";
inline constexpr const char* SoundGoal     = "resources/Audio/goal.wav";
inline constexpr const char* SoundGameOver = "resources/Audio/gameover.wav";
inline constexpr const char* MusicTrack    = "resources/Audio/music.mp3";
}  // namespace Paths

}  // namespace Config
