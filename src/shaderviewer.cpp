#include "shaderviewer.h"
#include "ui_shaderviewer.h"
#include <iostream>

ShaderViewer::ShaderViewer(Model model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShaderViewer),
    m_model(model)
{
    ui->setupUi(this);
}

ShaderViewer::~ShaderViewer()
{
    delete ui;
}


void ShaderViewer::loadGeometryClicked()
{
    std::cout << "Test loadGeometryClicked()" << std::endl;
}

void ShaderViewer::loadVertexClicked()
{
    std::cout << "Test loadVertexClicked()" << std::endl;
}

void ShaderViewer::loadFragmentClicked()
{
    std::cout << "Test loadFragmentClicked()" << std::endl;
}
