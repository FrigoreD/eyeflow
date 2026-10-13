#ifndef EYEFLOW_DOTWIDGET_H
#define EYEFLOW_DOTWIDGET_H
#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include "settings.h"

class DotWidget : public QWidget {
    Q_OBJECT

public:
    explicit DotWidget(const Settings &settings, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void tick();

    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    qreal m_phase{0.0};
    qint64 m_lastTickMs{0};
    qint64 m_activeMs{0};
    qreal m_periodSec{0.0};
    Settings m_settings;
    bool m_paused{false};
};


#endif //EYEFLOW_DOTWIDGET_H
