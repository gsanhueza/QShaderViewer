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
        std::cout << "SHADERVIEWER: Emitiendo señal..." << std::endl;
        emit emitModel(m_model);
        ui->actionCargarGeometra->setChecked(true);
    }
    else
    {
        std::cout << "SHADERVIEWER: Fallo al cargar archivo" << std::endl;
        ui->actionCargarGeometra->setChecked(false);
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
