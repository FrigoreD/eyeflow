#include "motion.h"

#include <algorithm>
#include <cmath>
#include <numbers>

namespace motion {
    double oscillation(double phase) {
        return std::sin(2.0 * std::numbers::pi * phase);
    }

    double fadeOpacity(const double activeMs, const double sessionDurationMs, const double fadeDurationMs) {
        const double show{activeMs / fadeDurationMs};
        const double hide{(sessionDurationMs - activeMs) / fadeDurationMs};

        return std::clamp(std::min(show, hide), 0.0, 1.0);
    }
}
