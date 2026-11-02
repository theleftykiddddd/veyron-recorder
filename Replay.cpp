#include "veyron/Replay.hpp"
namespace veyron {
bool ReplayScheduler::load(Macro macro) { if (!macro.isValid()) return false; m_macro=std::move(macro); m_cursor=0; m_state=ReplayState::Idle; return true; }
void ReplayScheduler::start() { if (!m_macro.inputs.empty()) { m_cursor=0; m_state=ReplayState::Playing; } }
void ReplayScheduler::pause() { if (m_state==ReplayState::Playing) m_state=ReplayState::Paused; }
void ReplayScheduler::resume() { if (m_state==ReplayState::Paused) m_state=ReplayState::Playing; }
void ReplayScheduler::stop() { m_cursor=0; m_state=ReplayState::Idle; }
std::size_t ReplayScheduler::advanceTo(std::uint64_t frame) {
    if (m_state!=ReplayState::Playing) return 0;
    const auto before=m_cursor;
    while (m_cursor<m_macro.inputs.size() && m_macro.inputs[m_cursor].frame<=frame) ++m_cursor;
    if (m_cursor==m_macro.inputs.size()) m_state=ReplayState::Finished;
    return m_cursor-before;
}
}
