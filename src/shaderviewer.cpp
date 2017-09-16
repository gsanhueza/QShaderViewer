#include "shaderviewer.h"
#include "ui_shaderviewer.h"

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

    if (m_model.loadGeometry(filepath.toStdString()))
    {
        ui->actionCargarGeometra->setChecked(true);
        ui->statusbar->showMessage("Geometría cargada.");
    }
    else
    {
        ui->actionCargarGeometra->setChecked(false);
        ui->statusbar->showMessage("Fallo al cargar geometría.");
    }

    // Enviar modelo solo si todo está cargado
    if (m_model.isEverythingLoaded())
    {
        ui->statusbar->showMessage("Listo.");
        emit emitModel(m_model);
    }
}

void ShaderViewer::loadVertexClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this);

    if (m_model.loadVertexShader(filepath.toStdString()))
    {
        ui->actionCargarVertex->setChecked(true);
        ui->statusbar->showMessage("Vertex cargado.");
    }
    else
    {
        ui->actionCargarVertex->setChecked(false);
        ui->statusbar->showMessage("Fallo al cargar vertex.");
    }

    // Enviar modelo solo si todo está cargado
    if (m_model.isEverythingLoaded())
    {
        ui->statusbar->showMessage("Listo.");
        emit emitModel(m_model);
    }
}

void ShaderViewer::loadFragmentClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this);

    if (m_model.loadFragmentShader(filepath.toStdString()))
    {
        ui->actionCargarVertex->setChecked(true);
        ui->statusbar->showMessage("Fragment cargado.");
    }
    else
    {
        ui->actionCargarFragment->setChecked(false);
        ui->statusbar->showMessage("Fallo al cargar fragment.");
    }

    // Enviar modelo solo si todo está cargado
    if (m_model.isEverythingLoaded())
    {
        ui->statusbar->showMessage("Listo.");
        emit emitModel(m_model);
    }
}
