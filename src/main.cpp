#include <QApplication>
#include "shaderviewer.h"
#include "model.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Model model;
    ShaderViewer viewer(model);

    viewer.show();

    return app.exec();
}
