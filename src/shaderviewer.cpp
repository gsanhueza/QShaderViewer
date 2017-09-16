#include "shaderviewer.h"
#include "ui_shaderviewer.h"

ShaderViewer::ShaderViewer(Model model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShaderViewer),
    m_model(model)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("Load your files to show them in the screen.");
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
        ui->actionLoadGeometry->setChecked(true);
        ui->statusbar->showMessage("Geometry loaded.");
    }
    else
    {
        ui->actionLoadGeometry->setChecked(false);
        ui->statusbar->showMessage("Failed to load geometry.");
    }

    // Send model to OGLWidget only if everything is already loaded.
    if (m_model.isEverythingLoaded())
    {
        ui->statusbar->showMessage("Ready.");
        emit emitModel(m_model);
    }
}

void ShaderViewer::loadVertexClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this);

    if (m_model.loadVertexShader(filepath.toStdString()))
    {
        ui->actionLoadVertex->setChecked(true);
        ui->statusbar->showMessage("Vertex shader loaded.");
    }
    else
    {
        ui->actionLoadVertex->setChecked(false);
        ui->statusbar->showMessage("Failed to load vertex shader.");
    }

    // Send model to OGLWidget only if everything is already loaded.
    if (m_model.isEverythingLoaded())
    {
        ui->statusbar->showMessage("Ready.");
        emit emitModel(m_model);
    }
}

void ShaderViewer::loadFragmentClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this);

    if (m_model.loadFragmentShader(filepath.toStdString()))
    {
        ui->actionLoadVertex->setChecked(true);
        ui->statusbar->showMessage("Fragment shader loaded.");
    }
    else
    {
        ui->actionLoadFragment->setChecked(false);
        ui->statusbar->showMessage("Failed to load fragment shader.");
    }

    // Send model to OGLWidget only if everything is already loaded.
    if (m_model.isEverythingLoaded())
    {
        ui->statusbar->showMessage("Ready.");
        emit emitModel(m_model);
    }
}
