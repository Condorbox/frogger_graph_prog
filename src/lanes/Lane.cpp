#include "lanes/Lane.h"

void Lane::Update(float dt) {
    for (auto& e : entities_) {
        e->Update(dt);
        Wrap(*e);
    }
}

void Lane::Draw() const {
    DrawBackground();
    for (const auto& e : entities_) e->Draw();
}
