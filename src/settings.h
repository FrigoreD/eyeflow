//
// Created by aagapov on 13.10.2026.
//

#ifndef EYEFLOW_SETTINGS_H
#define EYEFLOW_SETTINGS_H
#include <QtContainerFwd>
#include <QtTypes>

struct Settings {
    static constexpr qreal kPeriodMinSec{0.5};
    static constexpr qreal kPeriodMaxSec{8.0};

    qreal periodSec{2.0};
    qreal dotRadius{50.0};
};

Settings parseCommandLine(const QStringList &arguments);

#endif //EYEFLOW_SETTINGS_H
