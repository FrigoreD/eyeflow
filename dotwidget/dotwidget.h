//
// Created by aagapov on 11.10.2026.
//

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

private:
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
};


#endif //EYEFLOW_DOTWIDGET_H
