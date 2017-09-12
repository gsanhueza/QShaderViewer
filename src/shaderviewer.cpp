#include "shaderviewer.h"
#include "ui_shaderviewer.h"

ShaderViewer::ShaderViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShaderViewer)
{
    ui->setupUi(this);
}

ShaderViewer::~ShaderViewer()
{
    delete ui;
}
