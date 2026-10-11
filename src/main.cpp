#include <QApplication>

#include "dotwidget/dotwidget.h"

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};
    DotWidget window{};
    window.show();

    return app.exec();
}
