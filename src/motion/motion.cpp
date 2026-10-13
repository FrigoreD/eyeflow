#include "motion/motion.h"

#include <cmath>
#include <numbers>

namespace motion {

double oscillation(double phase) {
    return std::sin(2.0 * std::numbers::pi * phase);
}

}

