#include "settings.h"
#include <QCommandLineParser>
#include <QCommandLineOption>

Settings parseCommandLine(const QStringList &arguments) {
    QCommandLineParser parser;
    Settings settings{};
    const QCommandLineOption periodOption{
        {"p", "period"},
        "Time of one full cycle",
        "seconds",
        QString::number(settings.periodSec)
    };
    const QCommandLineOption radiusOption{
        {"r", "radius"},
        "Dot radius",
        "pixels",
        QString::number(settings.dotRadius)
    };

    parser.addHelpOption();
    parser.addOptions({periodOption, radiusOption});
    parser.process(arguments);

    if (parser.isSet(periodOption)) {
        bool ok{false};
        const qreal period{parser.value(periodOption).toDouble(&ok)};

        // Written as "not inside the range" so that NaN is rejected too.
        if (!ok || !(period >= Settings::kPeriodMinSec && period <= Settings::kPeriodMaxSec)) {
            QCommandLineParser::showMessageAndExit(
                QCommandLineParser::MessageType::Error,
                QString{"--period must be between %1 and %2 seconds\n"}
                .arg(Settings::kPeriodMinSec)
                .arg(Settings::kPeriodMaxSec),
                1
            );
        }

        settings.periodSec = period;
    }

    if (parser.isSet(radiusOption)) {
        bool ok{false};
        const qreal radius{parser.value(radiusOption).toDouble(&ok)};

        if (!ok || !(radius > 0.0)) {
            QCommandLineParser::showMessageAndExit(
                QCommandLineParser::MessageType::Error,
                "--radius must be a positive number\n",
                1
            );
        }

        settings.dotRadius = radius;
    }

    return settings;
}
