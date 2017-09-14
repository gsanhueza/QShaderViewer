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
    std::cout << "SHADERVIEWER: loadGeometryClicked()" << std::endl;

    if (m_model.loadGeometry("TODO: filepath va aquí"))
    {
        std::cout << "SHADERVIEWER: Geometry cargado, actualizar status bar" << std::endl;
        std::cout << "SHADERVIEWER: Esperar todos los datos, mostrar después con OGLWidget" << std::endl;
    }
}

void ShaderViewer::loadVertexClicked()
{
    std::cout << "SHADERVIEWER: loadVertexClicked()" << std::endl;
    if (m_model.loadVertexShader("TODO: filepath va aquí"))
    {
        std::cout << "SHADERVIEWER: Vertex cargado, actualizar status bar" << std::endl;
        std::cout << "SHADERVIEWER: Esperar todos los datos, mostrar después con OGLWidget" << std::endl;
    }
}

void ShaderViewer::loadFragmentClicked()
{
    std::cout << "SHADERVIEWER: loadFragmentClicked()" << std::endl;
    if (m_model.loadFragmentShader("TODO: filepath va aquí"))
    {
        std::cout << "SHADERVIEWER: Fragment cargado, actualizar status bar" << std::endl;
        std::cout << "SHADERVIEWER: Esperar todos los datos, mostrar después con OGLWidget" << std::endl;
    }
}
