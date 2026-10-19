#pragma once
#include "entities/Entity.h"
#include "world/WorldTypes.h"
#include <memory>
#include <vector>

class Frog;

// Abstract lane (one row of the map). Uses the Template Method pattern:
// Update() and Draw() are fixed, subclasses plug in Wrap(), DrawBackground()
// and Resolve().
class Lane {
public:
    explicit Lane(int row) : row_(row) {}
    virtual ~Lane() = default;

    void Update(float dt);
    void Draw() const;

    // Decides what this lane does to a frog standing on it this frame.
    virtual LaneOutcome Resolve(Frog& frog, float dt) const = 0;

    int Row() const { return row_; }

protected:
    virtual void DrawBackground() const = 0;
    virtual void Wrap(Entity& entity) const = 0;   // what happens at the screen edge
    void Add(std::unique_ptr<Entity> entity) { entities_.push_back(std::move(entity)); }

    int row_;
    std::vector<std::unique_ptr<Entity>> entities_;
};
