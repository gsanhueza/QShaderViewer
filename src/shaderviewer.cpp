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
    ui->statusbar->showMessage("Cargue sus archivos para mostrarlos en pantalla.");
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
        ui->statusbar->showMessage("Geometría cargada.");
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
        ui->statusbar->showMessage("Listo.");
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
        ui->actionCargarVertex->setChecked(true);
        ui->statusbar->showMessage("Vertex cargado.");
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
        ui->statusbar->showMessage("Listo.");
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
        ui->actionCargarVertex->setChecked(true);
        ui->statusbar->showMessage("Fragment cargado.");
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
        ui->statusbar->showMessage("Listo.");
        emit emitModel(m_model);
    }
}
