//
// Created by aagapov on 11.10.2026.
//

#include "motion/motion.h"

#include <cmath>
#include <numbers>

namespace motion {

double oscillation(double seconds, double periodSec) {
    return std::sin(2.0 * std::numbers::pi * seconds / periodSec);
}

}

