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
    m_model.loadGeometry("TODO: filepath va aquí");
}

void ShaderViewer::loadVertexClicked()
{
    std::cout << "Test loadVertexClicked()" << std::endl;
    m_model.loadVertexShader("TODO: filepath va aquí");
}

void ShaderViewer::loadFragmentClicked()
{
    std::cout << "Test loadFragmentClicked()" << std::endl;
    m_model.loadFragmentShader("TODO: filepath va aquí");
}
