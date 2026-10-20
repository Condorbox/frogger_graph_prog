#pragma once

// All tunable numbers and asset paths live here. No magic numbers elsewhere.
namespace Config {

inline constexpr const char* WindowTitle = "Frogger";
inline constexpr int TargetFps = 60;

// Grid
inline constexpr int Cell    = 50;
inline constexpr int Cols    = 16;
inline constexpr int Rows    = 14;
inline constexpr int ScreenW = Cell * Cols;   // 800
inline constexpr int ScreenH = Cell * Rows;   // 600

// Row layout (0 = top)
inline constexpr int GoalRow		= 0;
inline constexpr int RiverFirstRow	= 1;
inline constexpr int RiverLastRow	= 5;
inline constexpr int MedianRow		= 6;
inline constexpr int RoadFirstRow	= 7;
inline constexpr int RoadLastRow	= 11;
inline constexpr int StartRow		= 12;
inline constexpr int HudRow			= 13;
inline constexpr int TurtleRowA		= 2;
inline constexpr int TurtleRowB		= 5;

// Rules
inline constexpr int   NumSlots            = 5;
inline constexpr int   MaxLives            = 3;
inline constexpr float LevelTime           = 60.0f;   // seconds to fill every exit
inline constexpr float SpeedGrowthPerLevel = 0.12f;
inline constexpr int   SlotPoints          = 100;
inline constexpr int   LevelBonus          = 500;
inline constexpr int   TimeBonusPerSecond  = 10;
inline constexpr float MinCarGap		   = 80.0f;

// Frog animation
inline constexpr float HopDuration		= 0.12f;  // seconds the jump sprite is shown
inline constexpr float HopLift			= 8.0f;   // pixels the sprite rises mid-hop
inline constexpr float FrogSpriteScale	= 1.3f;   // sprite box relative to the old circle's diameter

// Turtle phases
inline constexpr float TurtleHiddenMin		= 1.5f;   
inline constexpr float TurtleHiddenMax		= 3.0f;
inline constexpr float TurtleDeadlyMin		= 1.0f;   
inline constexpr float TurtleDeadlyMax		= 2.0f;
inline constexpr float TurtleWarnTime		= 0.3f;    
inline constexpr float TurtleBlinkInterval	= 0.075f;  
inline constexpr float TurtleGhostAlpha		= 0.55f;  

constexpr bool IsRiverRow(int row) { return row >= RiverFirstRow && row <= RiverLastRow; }
constexpr bool IsTurtleRow(int row) { return row == TurtleRowA || row == TurtleRowB; }
constexpr bool IsLogRow(int row) { return IsRiverRow(row) && !IsTurtleRow(row); }
constexpr bool IsRoadRow(int row) { return row >= RoadFirstRow && row <= RoadLastRow; }
constexpr int  SlotColumn(int i) { return 1 + i * 3; }   // columns 1,4,7,10,13

// Asset paths (relative to the working directory).
// Maybe create a MusicCatalog and a Catalog parent 
namespace Paths {
inline constexpr const char* MusicTrack = "resources/Sounds/Lily_Islands.mp3";
}  // namespace Paths

namespace HUD {
inline constexpr int   Pad		 = 10;     // margin at the screen edges
inline constexpr int   Gap		 = 24;     // space between HUD sections
inline constexpr int   FontSize  = 20;
inline constexpr int   LifeSlot  = 32;     // width reserved per life icon
inline constexpr float LifeSize  = 11.0f;
inline constexpr int   BarWidth  = 120;
inline constexpr int   BarHeight = 16;
}  // namespace

}  // namespace Config
