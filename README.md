# Frogger (C++17 + raylib)

A Frogger clone: guide the frog across a road and a river and fill the five exits at the top before the level timer runs out.

## Build and run
```
cmake -B build
cmake --build build
./build/frogger        # run from the folder that contains "resources"
```
CMake uses an installed raylib if it finds one, otherwise it downloads raylib 5.5. If a `resources/` folder exists next to `CMakeLists.txt`, it is copied beside the executable.

**Controls:** Arrows / WASD to hop, ENTER to start, O for the "how to play" screen, R to restart after game over.

**Assets are all optional.** Missing textures or sounds are skipped and every entity has a drawn fallback (rounded rectangles, circles), so the game always runs. Paths live in `core/TextureCatalog.h`, `core/SoundCatalog.h` and `Config.h`.

---

## Gameplay decisions and why

**Grid and hopping.** The map is 16 x 14 cells of 50 px (800 x 600). The frog moves one cell per key press (`IsKeyPressed`, no key repeat). This keeps movement deliberate and readable, and makes every move a clear risk/reward decision. The only exception is the river: on log rows the frog's x is a free pixel value so a log can carry it, and it snaps back to the grid as soon as it hops onto a non-log row.

**Row layout.** Goal (row 0), river (1-5), median (6), road (7-11), start (12), HUD (13). A safe median in the middle splits the level into two halves, giving the player a place to breathe and plan the second half.

**Road.** Cars have a random speed (70-140 px/s) and lanes alternate direction by row parity. The frog's hitbox (30 x 30) is smaller than its cell on purpose, so near misses feel fair instead of cheap. Cars keep a minimum gap (`MinCarGap`) so a lane can never become an impassable wall.

**River.** The frog must stand on a log and is carried by it. Water, or being carried off screen, drowns it. The check uses the frog's *center* with a 6 px forgiveness margin at the log edges, so the player is not punished for pixel-level misjudgments. Each lane has one log type, with different speeds and gaps, so each row needs a different rhythm.

**Turtle lanes (our own twist).** In the original game turtles are platforms. Here the two "shallows" rows (2 and 5) are walkable, and the turtles are the *hazard*: they cycle between hidden (harmless), a short blinking warning (0.3 s), and surfaced (deadly). Turtles start in random phases so they are never in sync. This adds timing pressure in a different way from logs and road, and the warning blink keeps deaths readable. The "how to play" screen explains it.

**Exits.** There are five slots (columns 1, 4, 7, 10, 13). Hopping up into the goal row anywhere else, or into an already filled slot, is simply blocked, with no life lost. Blocking, instead of killing, avoids frustrating deaths on the very last hop. After filling a slot, the frog returns to the start.

**Lives, timer, scoring.** 3 lives and 60 s per level. The timer is shared across lives (dying does not reset it), which keeps pressure on and prevents stalling; if it expires, the player loses a life and the timer and frog restart. Score: 100 per exit, plus 500 + 10 per second left when a level is cleared, so playing fast is rewarded. Each level increases lane speeds by 12% (`SpeedGrowthPerLevel`), a simple linear curve that is easy to tune.

**Feedback.** Sound for hop, hit, splash, goal and game over; a sprite change and small lift while hopping; a HUD bar that turns red under 25% of the time.

---

## Architecture

```
src/
  main.cpp, Config.h, Theme.h      entry point, all constants/paths, colors
  core/      Game, GameState, GameSession, ResourceManager, AudioManager,
             TextureCatalog, SoundCatalog, CatalogCheck
  states/    TitleState, PlayingState, GameOverState, OptionsState
  world/     World, GoalRow, LaneFactory, WorldTypes, TileUtils
  lanes/     Lane (abstract), SafeLane, RoadLane, RiverLane, TurtleLane
  entities/  Entity (abstract), Car, Log, Turtle, Frog
  ui/        Hud, TextUtils
```

The main idea is **separation of responsibilities**, with dependencies pointing in one direction:

- `World` is the simulation (frog, goal, lanes). It knows nothing about lives, score, timers or audio. It only reports `WorldEvent`s.
- `GameSession` holds the rules data (lives, score, level, timer). It knows nothing about drawing or input.
- `PlayingState` is the glue: it reads input, updates the world, then reacts to the events (score, lives, sound).
- `Hud` is a read-only view of the session.

Because of this, rules can be changed without touching the simulation, and the simulation can be changed without touching the rules.

### Patterns used
- **State** (`GameState` and its subclasses): one class per screen. `Game::ChangeState` is *deferred* to the end of the frame, so a state can safely replace itself from inside its own `Update()`.
- **Template Method** (`Lane`): `Update()` and `Draw()` are fixed; subclasses plug in `Wrap()` and `DrawBackground()`.
- **Polymorphism / Strategy-like** (`Lane::Resolve`): each lane decides what happens to the frog (safe, killed, drowned), so `World` has no `if (isRiver)` chains. Adding a lane type means adding one class.
- **Factory** (`LaneFactory::BuildLevel`): builds all lanes of a level from small spec tables, including the speed scaling.
- **Event queue** (`WorldEvent`): decouples the simulation from rules and audio.
- **Singleton** (`ResourceManager`, `AudioManager`): single global owners of textures and sounds. They have explicit `Init/Shutdown` and `LoadAll/UnloadAll` because raylib needs the window and audio device to exist during loading and unloading. `Game` owns that lifetime (**RAII**).
- **Data-driven catalogs**: `kTextureCatalog` and `kSoundCatalog` are the single source of truth for assets, and `CatalogMatchesEnum` with `static_assert` makes the build fail if an enum value and its table row ever get out of sync.
- **No magic numbers**: tunable values live in `Config.h`, so balancing the game does not require touching logic.

### Known limitations / ideas
- `RiverLane::Wrap` only handles left-to-right logs (all current river lanes move that way); a bidirectional version would mirror `RoadLane::Wrap`.
- Level difficulty only scales speed; no new lane layouts per level yet.
- No persistent high score.
- The Singletons are a deliberate trade-off for simplicity; passing the managers in explicitly would make the code easier to unit test.
