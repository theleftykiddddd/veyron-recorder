#include "veyron/Recorder.hpp"
namespace veyron {
bool Recorder::begin(MacroMetadata metadata, std::uint64_t startFrame) {
    if (m_state == RecorderState::Recording) return false;
    reset(); m_macro.metadata = std::move(metadata); m_startFrame = startFrame;
    m_state = RecorderState::Recording; return true;
}
bool Recorder::record(int button, bool player2, bool down, std::uint64_t gameFrame) {
    if (m_state != RecorderState::Recording || gameFrame < m_startFrame) return false;
    m_macro.inputs.push_back({gameFrame - m_startFrame, button, player2, down});
    return true;
}
std::optional<Macro> Recorder::stop() {
    if (m_state != RecorderState::Recording) return std::nullopt;
    m_state = RecorderState::Stopped; m_macro.sortByFrameStable();
    return m_macro;
}
void Recorder::reset() { m_macro = {}; m_startFrame = 0; m_state = RecorderState::Idle; }
}
