#include <QApplication>
#include "qshaderviewer.h"
#include "model.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Model model;
    QShaderViewer viewer(model);

    viewer.show();

    return app.exec();
}
