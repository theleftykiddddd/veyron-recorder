#pragma once
#include "Macro.hpp"
#include <cstdint>
#include <optional>

namespace veyron {

enum class RecorderState { Idle, Recording, Stopped };

// Platform-neutral recorder. The Geode input hook must call begin(), record(),
// and stop() with the game's authoritative frame counter.
class Recorder {
public:
    bool begin(MacroMetadata metadata, std::uint64_t startFrame);
    bool record(int button, bool player2, bool down, std::uint64_t gameFrame);
    std::optional<Macro> stop();
    void reset();
    [[nodiscard]] RecorderState state() const { return m_state; }
    [[nodiscard]] const Macro& current() const { return m_macro; }
private:
    RecorderState m_state = RecorderState::Idle;
    Macro m_macro;
    std::uint64_t m_startFrame = 0;
};
}
