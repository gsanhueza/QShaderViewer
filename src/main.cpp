#include "canvas.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Canvas w;
    w.show();

    return app.exec();
}

