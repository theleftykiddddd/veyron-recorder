#pragma once
#include "Macro.hpp"
#include <cstddef>
#include <cstdint>
namespace veyron {
enum class ReplayState { Idle, Playing, Paused, Finished };
// Scheduler only: a Geode adapter is responsible for injecting inputs into GD.
class ReplayScheduler {
public:
    bool load(Macro macro);
    void start(); void pause(); void resume(); void stop();
    // Returns the next event range due at this macro frame. It never injects input.
    std::size_t advanceTo(std::uint64_t frame);
    [[nodiscard]] const Macro& macro() const { return m_macro; }
    [[nodiscard]] ReplayState state() const { return m_state; }
    [[nodiscard]] std::size_t cursor() const { return m_cursor; }
private:
    Macro m_macro; std::size_t m_cursor = 0; ReplayState m_state = ReplayState::Idle;
};
}
