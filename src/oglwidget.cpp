#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget* parent)
    : QOpenGLWidget(parent),
      m_program(0),
      m_xRot(0),
      m_yRot(0),
      m_zRot(0)
{
}

OGLWidget::~OGLWidget()
{
    cleanup();
}

void OGLWidget::cleanup()
{
    makeCurrent();
    m_vbo.destroy();
    delete m_program;
    m_program = nullptr;
    doneCurrent();
}

void OGLWidget::setupVertexAttribs()
{
    m_vbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_vbo.release();
}

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    generateGLProgram();
}

void OGLWidget::generateGLProgram()
{
    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, QString(m_model.getVertexPath().c_str()));
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, QString(m_model.getFragmentPath().c_str()));
    m_program->bindAttributeLocation("vertex", 0);
    m_program->bindAttributeLocation("normal", 1);
    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
    m_lightPosLoc = m_program->uniformLocation("lightPos");

    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Here you can write fixed geometries, if you don't need to load them more than once.

    // Our camera never changes in this example.
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -1);

    // Light position is fixed.
    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_program->release();
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_world.setToIdentity();

    // Allow rotation of the world
    m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();
    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

    // Setup our vertex buffer object.
    m_vbo.create();
    m_vbo.bind();

    // Clear old geometry data from vector.
    m_data.clear();

    // Load geometry from local file
    for (vector<float> point : m_model.getCoordinates())
    {
        m_data.append(static_cast<float>(point.at(0)) / 100);
        m_data.append(static_cast<float>(point.at(1)) / 100);
        m_data.append(static_cast<float>(point.at(2)) / 100);
    }

    m_vbo.allocate(m_data.constData(), m_data.count() * sizeof(GLfloat));

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();

    glDrawArrays(GL_TRIANGLES, 0, m_data.count() / 3);

    m_program->release();
}

void OGLWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void OGLWidget::receiveModel(const Model &m)
{
    m_model = m;
    m_program = nullptr;
    generateGLProgram();
    update();
}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void OGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(m_xRot + 8 * dy);
        setZRotation(m_zRot + 8 * dx);
    }
    m_lastPos = event->pos();
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void OGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        update();
    }
}

void OGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        update();
    }
}

void OGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        update();
    }
}
