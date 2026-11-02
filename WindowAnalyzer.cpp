#include "veyron/WindowAnalyzer.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>

namespace veyron {

std::vector<WindowBand> WindowAnalyzer::defaultBands() {
    return {
        {0, 1, "0-1F", 0xF04B68},
        {2, 2, "2F", 0xFFBD70},
        {3, 3, "3F", 0xF8FF72},
        {4, 4, "4F", 0xF4F4F4},
        {5, 6, "5-6F", 0x8BE995},
        {7, 8, "7-8F", 0x9CCEFF},
        {9, 12, "9-12F", 0x897DEB},
        {13, 16, "13-16F", 0xB78BEE},
        {17, 24, "17-24F", 0xDB74E8}
    };
}

std::size_t WindowAnalyzer::findBand(const std::vector<WindowBand>& bands, int frames) {
    for (std::size_t i = 0; i < bands.size(); ++i) {
        if (frames >= bands[i].minFrames && frames <= bands[i].maxFrames) {
            return i;
        }
    }
    return bands.size();
}

WindowStats WindowAnalyzer::summarize(
    const std::vector<MeasuredClick>& clicks,
    const std::vector<WindowBand>& bands
) {
    WindowStats result;
    result.bands = bands;
    result.counts.assign(bands.size(), 0);

    std::int64_t totalFrames = 0;
    bool hasMeasurement = false;

    for (const auto& click : clicks) {
        if (click.windowFrames < 0) {
            ++result.unknown;
            continue;
        }

        ++result.measured;
        const auto band = findBand(bands, click.windowFrames);
        if (band < result.counts.size()) {
            ++result.counts[band];
        }

        if (!hasMeasurement) {
            result.minimumFrames = click.windowFrames;
            result.maximumFrames = click.windowFrames;
            hasMeasurement = true;
        } else {
            result.minimumFrames = std::min(result.minimumFrames, click.windowFrames);
            result.maximumFrames = std::max(result.maximumFrames, click.windowFrames);
        }
        totalFrames += click.windowFrames;
    }

    if (result.measured > 0) {
        result.averageFrames = static_cast<double>(totalFrames) /
                              static_cast<double>(result.measured);
    }
    return result;
}

double WindowAnalyzer::toneFrequencyHz(int windowFrames, int minFrames,
                                       int maxFrames, double lowHz,
                                       double highHz) {
    if (maxFrames <= minFrames) return lowHz;
    const double clamped = std::clamp(
        static_cast<double>(windowFrames),
        static_cast<double>(minFrames),
        static_cast<double>(maxFrames)
    );
    const double t = (clamped - minFrames) / (maxFrames - minFrames);
    return lowHz + t * (highHz - lowHz);
}

} // namespace veyron
