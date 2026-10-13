#ifndef EYEFLOW_MOTION_H
#define EYEFLOW_MOTION_H

namespace motion {
    double oscillation(double phase);
    double fadeOpacity(double activeMs, double sessionDurationMs, double fadeDurationMs);
}


#endif //EYEFLOW_MOTION_H
