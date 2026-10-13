#include <QApplication>

#include "dotwidget.h"

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};

    const Settings settings{parseCommandLine(app.arguments())};
    DotWidget window{settings};
    window.show();

    return app.exec();
}
