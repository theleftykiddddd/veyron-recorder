#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace veyron {

// Button values are intentionally kept opaque here. Import/export adapters map
// the numeric value used by each replay format to the Geometry Dash button.
struct InputEvent {
    std::uint64_t frame = 0;
    int button = 0;
    bool player2 = false;
    bool down = false;
};

struct MacroMetadata {
    std::string title;
    std::string author;
    std::uint32_t levelId = 0;
    std::string levelName;
    double gameVersion = 2.2091;
    double tickRate = 240.0;
    std::string sourceFormat = "veyron-json";
};

struct Macro {
    MacroMetadata metadata;
    std::vector<InputEvent> inputs;

    // Stable sorting is important: press/release events at the same frame must
    // keep their original order when imported from another format.
    void sortByFrameStable();
    [[nodiscard]] bool isValid(std::string* reason = nullptr) const;
};

} // namespace veyron
