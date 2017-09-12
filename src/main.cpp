#include "shaderviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ShaderViewer w;
    w.show();

    return app.exec();
}
