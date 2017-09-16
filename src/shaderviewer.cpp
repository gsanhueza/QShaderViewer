#include "shaderviewer.h"
#include "ui_shaderviewer.h"
#include <iostream>

static const bool DEBUG = true;

void svdebug(string s)
{
    if (DEBUG)
    {
        std::cout << s << std::endl;
    }
}

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

    svdebug("SHADERVIEWER: loadGeometryClicked()");
    if (m_model.loadGeometry(filepath.toStdString()))
    {
        svdebug("SHADERVIEWER: Geometry cargado, actualizar status bar");
        svdebug("SHADERVIEWER: Esperar todos los datos, mostrar después con OGLWidget");
        ui->actionCargarGeometra->setChecked(true);
    }
    else
    {
        svdebug("SHADERVIEWER: Fallo al cargar geometría");
        ui->actionCargarGeometra->setChecked(false);
    }

    // Enviar modelo solo si todo está cargado
    if (m_model.isEverythingLoaded())
    {
        svdebug("SHADERVIEWER: Emitiendo señal...");
        emit emitModel(m_model);
    }
}

void ShaderViewer::loadVertexClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this);

    svdebug("SHADERVIEWER: loadVertexClicked()");
    if (m_model.loadVertexShader(filepath.toStdString()))
    {
        svdebug("SHADERVIEWER: Vertex cargado, actualizar status bar");
        svdebug("SHADERVIEWER: Esperar todos los datos, mostrar después con OGLWidget");
    }
    else
    {
        svdebug("SHADERVIEWER: Fallo al cargar vertex");
        ui->actionCargarVertex->setChecked(false);
    }

    // Enviar modelo solo si todo está cargado
    if (m_model.isEverythingLoaded())
    {
        svdebug("SHADERVIEWER: Emitiendo señal...");
        emit emitModel(m_model);
    }
}

void ShaderViewer::loadFragmentClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this);

    svdebug("SHADERVIEWER: loadFragmentClicked()");
    if (m_model.loadFragmentShader(filepath.toStdString()))
    {
        svdebug("SHADERVIEWER: Fragment cargado, actualizar status bar");
        svdebug("SHADERVIEWER: Esperar todos los datos, mostrar después con OGLWidget");
    }
    else
    {
        svdebug("SHADERVIEWER: Fallo al cargar fragment");
        ui->actionCargarFragment->setChecked(false);
    }

    // Enviar modelo solo si todo está cargado
    if (m_model.isEverythingLoaded())
    {
        svdebug("SHADERVIEWER: Emitiendo señal...");
        emit emitModel(m_model);
    }
}
