#include "qshaderviewer.h"
#include "ui_qshaderviewer.h"

QShaderViewer::QShaderViewer(Model model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QShaderViewer),
    m_tutorial(new Tutorial),
    m_about(new About),
    m_model(model)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("Load your files to show them in the screen.");

    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();

    int x = (screenWidth - this->width()) / 2;
    int y = (screenHeight - this->height()) / 2;
    this->move(x, y);
}

QShaderViewer::~QShaderViewer()
{
    delete m_tutorial;
    delete m_about;
    delete ui;
}

void QShaderViewer::loadGeometryClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Geometry files"), ".", tr("Geometry files (*)"));

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

void QShaderViewer::loadVertexClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Vertex shaders"), ".", tr("Vertex shaders (*.glsl)"));

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

void QShaderViewer::loadFragmentClicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Fragment shaders"), ".", tr("Fragment shaders (*.glsl)"));

    if (m_model.loadFragmentShader(filepath.toStdString()))
    {
        ui->actionLoadFragment->setChecked(true);
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

void QShaderViewer::loadTutorialClicked()
{
    m_tutorial->show();
}

void QShaderViewer::loadAboutClicked()
{
    m_about->show();
}

void QShaderViewer::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);
}
