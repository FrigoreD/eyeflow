#include "dotwidget.h"
#include "motion.h"
#include <QPainter>
#include <chrono>
#include <QKeyEvent>
#include <algorithm>

using namespace std::chrono_literals;

namespace {
    constexpr qreal kPeriodStep{1.2};
    constexpr auto kFrameInterval{8ms};
    constexpr qreal kAmplitudeRatio{0.4};
    constexpr double kFadeDurationMs{1500.0};
}

DotWidget::DotWidget(const Settings &settings, QWidget *parent) : QWidget{parent}, m_periodSec{settings.periodSec},
                                                                  m_settings{settings} {
    connect(&m_timer, &QTimer::timeout, this, &DotWidget::tick);
    m_timer.start(kFrameInterval);
    m_elapsedTimer.start();

    resize(QSize{1600, 600});
    setWindowTitle("EyeFlow");
}

void DotWidget::paintEvent(QPaintEvent */*event*/) {
    const qreal amplitude{kAmplitudeRatio * rect().width()};
    const QPointF center{rect().center()};
    const qreal offset{amplitude * motion::oscillation(m_phase)};
    const QPointF dotCenter{offset + center.x(), center.y()};
    const double opacity{
        motion::fadeOpacity(
            static_cast<double>(m_activeMs),
            static_cast<double>(m_settings.sessionDurationSec * 1000),
            kFadeDurationMs
        )
    };

    QRadialGradient gradient{dotCenter, m_settings.dotRadius};
    gradient.setColorAt(0.0, QColor{255, 200, 140});
    gradient.setColorAt(0.7, QColor{255, 130, 40});
    gradient.setColorAt(1.0, QColor{255, 130, 40, 0});

    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.fillRect(rect(), QColor{0, 0, 0});
    painter.setOpacity(opacity);

    painter.drawEllipse(dotCenter, m_settings.dotRadius, m_settings.dotRadius);
}

void DotWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Space:
            if (event->isAutoRepeat()) {
                break;
            }

            m_paused = !m_paused;
            break;
        case Qt::Key_Up:
            m_periodSec = std::clamp(m_periodSec / kPeriodStep, Settings::kPeriodMinSec, Settings::kPeriodMaxSec);
            break;
        case Qt::Key_Down:
            m_periodSec = std::clamp(m_periodSec * kPeriodStep, Settings::kPeriodMinSec, Settings::kPeriodMaxSec);
            break;
        case Qt::Key_Escape:
            close();
            break;
        default:
            QWidget::keyPressEvent(event);
            break;
    }
}

void DotWidget::tick() {
    const qint64 nowMs{m_elapsedTimer.elapsed()};
    const qint64 dt{nowMs - m_lastTickMs};
    m_lastTickMs = nowMs;

    if (!m_paused) {
        m_activeMs += dt;
        if (m_activeMs >= m_settings.sessionDurationSec * 1000) {
            close();
            m_timer.stop();
            return;
        }
        m_phase += static_cast<qreal>(dt) / 1000.0 / m_periodSec;
    }

    update();
}
