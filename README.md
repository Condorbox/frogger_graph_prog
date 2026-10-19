# Frogger (C++17 + raylib)

## Build
```
cmake -B build
cmake --build build
./build/frogger        # run from the folder that contains "resources"
```
CMake uses an installed raylib if it finds one, otherwise downloads raylib 5.5.
If a `resources/` folder exists next to `CMakeLists.txt` it is copied beside the executable.

## Assets (all optional, missing files are skipped)
```
resources/Game/Enemies/Log1U.png  Log2U.png  Log4U.png
resources/Audio/hop.wav hit.wav splash.wav goal.wav gameover.wav music.mp3
```
Paths live in `src/Config.h`.

## Architecture
```
src/
  main.cpp                 creates Game and runs it
  Config.h  Theme.h        constants, asset paths, colors
  core/
    Game                   window + main loop + state machine
    GameState              interface for screens (State pattern)
    GameSession            lives, score, level, timer (rules only)
    ResourceManager        Singleton: textures
    AudioManager           Singleton: sounds + music
  states/
    TitleState  PlayingState  GameOverState
  world/
    World                  simulation: frog + goal + lanes, emits events
    GoalRow                the 5 exits
    LaneFactory            Factory: builds the lanes of a level
    WorldTypes.h           Direction, LaneOutcome, WorldEvent
  lanes/
    Lane (abstract)        Template Method: Update/Draw fixed, hooks vary
    SafeLane  RoadLane  RiverLane
  entities/
    Entity (abstract)      moving thing with bounds + speed
    Car  Log               Entity subclasses
    Frog                   the player
  ui/
    Hud  TextUtils.h
```

### Patterns used
- **Singleton** (`ResourceManager`, `AudioManager`): global, single-owner resources, with explicit Init/Shutdown because raylib needs the window alive.
- **State**: `GameState` + Title/Playing/GameOver. Changes are deferred to the end of the frame.
- **Template Method**: `Lane::Update/Draw` call virtual `Wrap`, `DrawBackground`.
- **Polymorphism / Strategy-like**: `Lane::Resolve` decides what each lane does to the frog.
- **Factory**: `LaneFactory::BuildLevel`.
- **Event queue**: `World` reports `WorldEvent`s, `PlayingState` reacts (score, lives, sound). World never touches rules or audio.
- **RAII**: `Game` owns window/audio/resources for its lifetime.
