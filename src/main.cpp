#include <QApplication>

#include "dotwidget.h"

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};

    constexpr Settings settings{};
    DotWidget window{settings};
    window.show();

    return app.exec();
}
