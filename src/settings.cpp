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
    const QCommandLineOption durationOption{
        {"d", "duration"},
        "Session duration",
        "seconds",
        QString::number(settings.sessionDurationSec)
    };

    parser.addHelpOption();
    parser.addOptions({periodOption, radiusOption, durationOption});
    parser.process(arguments);

    if (parser.isSet(periodOption)) {
        bool ok{false};
        const qreal period{parser.value(periodOption).toDouble(&ok)};

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

    if (parser.isSet(durationOption)) {
        bool ok{false};
        const qint64 duration{parser.value(durationOption).toInt(&ok)};

        if (!ok || duration <= 0) {
            QCommandLineParser::showMessageAndExit(
                QCommandLineParser::MessageType::Error,
                "--duration must be a positive number\n",
                1
            );
        }

        settings.sessionDurationSec = duration;
    }

    return settings;
}
