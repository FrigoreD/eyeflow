#ifndef EYEFLOW_DOTWIDGET_H
#define EYEFLOW_DOTWIDGET_H
#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>


class DotWidget : public QWidget {
    Q_OBJECT

public:
    explicit DotWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    qreal m_phase{0.0};
    qint64 m_lastTickMs{0};
    qreal m_periodSec{0.0};

    void tick();
};


#endif //EYEFLOW_DOTWIDGET_H
