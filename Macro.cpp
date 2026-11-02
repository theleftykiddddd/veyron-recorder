#include "veyron/Macro.hpp"

#include <algorithm>
#include <cmath>

namespace veyron {

void Macro::sortByFrameStable() {
    std::stable_sort(inputs.begin(), inputs.end(), [](const InputEvent& a, const InputEvent& b) {
        return a.frame < b.frame;
    });
}

bool Macro::isValid(std::string* reason) const {
    auto fail = [reason](const char* message) {
        if (reason) *reason = message;
        return false;
    };

    if (metadata.tickRate <= 0.0 || !std::isfinite(metadata.tickRate)) {
        return fail("Tick rate must be a finite value greater than zero.");
    }
    if (inputs.empty()) {
        return fail("The macro contains no input events.");
    }
    for (std::size_t i = 1; i < inputs.size(); ++i) {
        if (inputs[i].frame < inputs[i - 1].frame) {
            return fail("Input events are not sorted by frame.");
        }
    }
    return true;
}

} // namespace veyron
