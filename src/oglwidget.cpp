#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_POLYGON);
    for (vector<float> point : m_model.getCoordinates())
    {
        float R = static_cast<double>(rand()) / RAND_MAX;
        float G = static_cast<double>(rand()) / RAND_MAX;
        float B = static_cast<double>(rand()) / RAND_MAX;
        glColor3f (R, G, B);
        glVertex3f(point.at(0) / 10, point.at(1) / 10, point.at(2) / 10);
    }
    glEnd();
}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//     gluPerspective(45, (float) w / h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//     gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

void OGLWidget::receiveModel(const Model &m)
{
    std::cout << "OGLWIDGET: Recibiendo señal" << std::endl;
    m_model = m;
}
