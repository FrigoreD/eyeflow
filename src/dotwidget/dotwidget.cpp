#include "dotwidget/dotwidget.h"
#include "motion/motion.h"
#include <QPainter>
#include <chrono>
#include <QKeyEvent>
#include <QDebug>

using namespace std::chrono_literals;

namespace {
    constexpr auto kFrameInterval{8ms};
    constexpr qreal kPeriodSec{2.0};
    constexpr qreal kAmplitudeRatio{0.4};
    constexpr qreal kDotRadius{50.0};
}

DotWidget::DotWidget(QWidget *parent) : QWidget{parent} {
    connect(&m_timer, &QTimer::timeout, this, [this]() { update(); });
    m_timer.start(kFrameInterval);
    m_elapsedTimer.start();

    resize(QSize{1600, 600});
    setWindowTitle("EyeFlow");
}

void DotWidget::paintEvent(QPaintEvent *event) {
    const qreal amplitude{kAmplitudeRatio * rect().width()};
    const QPointF center{rect().center()};
    const qreal seconds{static_cast<qreal>(m_elapsedTimer.elapsed()) / 1000.0};
    const qreal offset{amplitude * motion::oscillation(seconds, kPeriodSec)};
    const QPointF dotCenter{offset + center.x(), center.y()};

    QRadialGradient gradient{dotCenter, kDotRadius};
    gradient.setColorAt(0.0, QColor{255, 200, 140});
    gradient.setColorAt(0.7, QColor{255, 130, 40});
    gradient.setColorAt(1.0, QColor{255, 130, 40, 0});

    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.fillRect(rect(), QColor{0, 0, 0});

    painter.drawEllipse(dotCenter, kDotRadius, kDotRadius);

    QWidget::paintEvent(event);
}

void DotWidget::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    qDebug() << "key pressed:" << key;
}
