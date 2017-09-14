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
    QString filepath = QFileDialog::getOpenFileName(this);

    std::cout << "SHADERVIEWER: loadGeometryClicked()" << std::endl;
    if (m_model.loadGeometry(filepath.toStdString()))
    {
        std::cout << "SHADERVIEWER: Geometry cargado, actualizar status bar" << std::endl;
        std::cout << "SHADERVIEWER: Esperar todos los datos, mostrar después con OGLWidget" << std::endl;
    }
}

void ShaderViewer::loadVertexClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this);

    std::cout << "SHADERVIEWER: loadVertexClicked()" << std::endl;
    if (m_model.loadVertexShader(filepath.toStdString()))
    {
        std::cout << "SHADERVIEWER: Vertex cargado, actualizar status bar" << std::endl;
        std::cout << "SHADERVIEWER: Esperar todos los datos, mostrar después con OGLWidget" << std::endl;
    }
}

void ShaderViewer::loadFragmentClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this);

    std::cout << "SHADERVIEWER: loadFragmentClicked()" << std::endl;
    if (m_model.loadFragmentShader(filepath.toStdString()))
    {
        std::cout << "SHADERVIEWER: Fragment cargado, actualizar status bar" << std::endl;
        std::cout << "SHADERVIEWER: Esperar todos los datos, mostrar después con OGLWidget" << std::endl;
    }
}
