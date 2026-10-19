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

// Frog animation
inline constexpr float HopDuration		= 0.12f;  // seconds the jump sprite is shown
inline constexpr float HopLift			= 8.0f;   // pixels the sprite rises mid-hop
inline constexpr float FrogSpriteScale	= 1.3f;   // sprite box relative to the old circle's diameter

constexpr bool IsRiverRow(int row) { return row >= RiverFirstRow && row <= RiverLastRow; }
constexpr bool IsRoadRow(int row)  { return row >= RoadFirstRow  && row <= RoadLastRow; }
constexpr int  SlotColumn(int i)   { return 1 + i * 3; }   // columns 1,4,7,10,13

// Asset paths (relative to the working directory). Missing files are skipped safely.
namespace Paths {
inline constexpr const char* Log1U           = "resources/Game/Enemies/Log1U.png";
inline constexpr const char* Log2U           = "resources/Game/Enemies/Log2U.png";
inline constexpr const char* Log4U		     = "resources/Game/Enemies/Log4U.png";
inline constexpr const char* SoundHop        = "resources/Sounds/frogger_hop.wav";
inline constexpr const char* SoundHit        = "resources/Sounds/frogger_plunk.wav";
inline constexpr const char* SoundSplash     = "resources/Sounds/splash.wav";
inline constexpr const char* SoundGoal       = "resources/Sounds/goal.wav";
inline constexpr const char* SoundGameOver   = "resources/Sounds/Game_Over.mp3";
inline constexpr const char* MusicTrack      = "resources/Sounds/Lily_Islands.mp3";
inline constexpr const char* PlayerUp	     = "resources/Game/Player_F.png";
inline constexpr const char* PlayerDown      = "resources/Game/Player_D.png";
inline constexpr const char* PlayerLeft      = "resources/Game/Player_L.png";
inline constexpr const char* PlayerRight     = "resources/Game/Player_R.png";
inline constexpr const char* PlayerJumpUp    = "resources/Game/PlayerJump_F.png";
inline constexpr const char* PlayerJumpDown  = "resources/Game/PlayerJump_D.png";
inline constexpr const char* PlayerJumpLeft  = "resources/Game/PlayerJump_L.png";
inline constexpr const char* PlayerJumpRight = "resources/Game/PlayerJump_R.png";
}  // namespace Paths

}  // namespace Config
