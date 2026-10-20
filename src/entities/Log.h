#pragma once
#include "entities/Entity.h"
#include "Config.h"

enum class LogType { Log1U, Log2U, Log4U };

class Log final : public Entity {
public:
    static constexpr float Height = static_cast<float>(Config::Cell - 2 * Config::LogInset);

    Log(float x, int row, LogType type, float speed);
    void Draw() const override;

    // Width depends on the texture (if loaded) so every log keeps its aspect ratio.
    static float WidthFor(LogType type);

private:
    LogType type_;
};
