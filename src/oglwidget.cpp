#include <iostream>
#include "oglwidget.h"
#include <cmath>

OGLWidget::OGLWidget(QWidget* parent)
    : QOpenGLWidget(parent),
      m_program(0),
      m_xRot(0),
      m_yRot(0),
      m_zRot(0),
      m_xLight(0),
      m_yLight(0),
      m_zLight(30),
      m_xCamPos(0),
      m_yCamPos(0),
      m_zCamPos(-5),
      m_dataAlreadyLoaded(false)
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
    f->glEnableVertexAttribArray(0); // Vertex
    f->glEnableVertexAttribArray(1); // Normal
    // glVertexAttribPointer(GLuint index​, GLint size​, GLenum type​, GLboolean normalized​, GLsizei stride​, const GLvoid * pointer​);
    // index = Vertex(0) or Normal(1), can be more if needed
    // size = Coordinates(x, y, z) => 3
    // type = GL_FLOAT, as that's the type of each coordinate
    // normalized = false, as there's no need to normalize here
    // stride = 0, which implies that vertices are side-to-side (VVVNNN)
    // pointer = where is the start of the data (in VVVNNN, 0 = start of vertices and GL_FLOAT * size(vertexArray) = start of normals)
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(GL_FLOAT) * sizeof(m_model.getVertices().size())));
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
    m_modelViewMatrixLoc = m_program->uniformLocation("modelViewMatrix");
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
    m_lightPosLoc = m_program->uniformLocation("lightPos");

    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Here you can write fixed geometries, if you don't need to load them more than once.

    // Our camera has a initial position.
    m_camera.setToIdentity();
//     m_camera.translate(m_xCamPos, m_yCamPos, m_zCamPos);
    m_camera.lookAt(QVector3D(0, 0, -5), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

    m_program->release();
}

void OGLWidget::loadData()
{
    // Setup our vertex buffer object.
    m_vbo.create();
    m_vbo.bind();

    // Clear old geometry data from vector.
    m_data.clear();

    // Load geometry (vertices) from local file
    for (float point : m_model.getVertices())
    {
        m_data.append(point);
    }

    // Load geometry (normals) from local file
    for (float point : m_model.getNormals())
    {
        m_data.append(point);
    }

    // Allocate data into VBO
    m_vbo.allocate(m_data.constData(), m_data.count() * sizeof(GLfloat));

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();
    m_dataAlreadyLoaded = true;
}

void OGLWidget::paintGL()
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_world.setToIdentity();

    // Allow rotation of the world
    m_world.rotate(m_xRot / 16.0f, 1, 0, 0);
    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Bind data of shaders to program
    m_program->bind();
    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_modelViewMatrixLoc, m_camera * m_world);
    QMatrix3x3 normalMatrix = (m_camera * m_world).normalMatrix();
    m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);
    m_program->setUniformValue(m_lightPosLoc, QVector3D(m_xLight, m_yLight, m_zLight));

    // Load new data only on geometry or shader change
    if (not m_dataAlreadyLoaded)
    {
        cout << "Loading data..." << endl;
        loadData();
    }

    // Draw triangulation
    glDrawArrays(GL_TRIANGLES, 0, m_data.count() / 3); // Last argument = Number of vertices

    cout << "Light  : (" << m_xLight << ", " << m_yLight << ", " << m_zLight << ")" << endl;
    cout << "Camera : (" << m_xCamPos << ", " << m_yCamPos << ", " << m_zCamPos << ")" << endl;
    cout << "Rotate : (" << m_xRot / 16 << ", " << m_yRot / 16 << ", " << m_zRot / 16 << ")" << endl;
    cout << endl;

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
    m_dataAlreadyLoaded = false;
    generateGLProgram();
    update();
}

void OGLWidget::keyPressed(QKeyEvent *event)
{
    // Plus and Minus keys move the camera
    // WASDQE move the light
    switch(event->key())
    {
        // Camera movement
        case Qt::Key_Plus:
            m_zCamPos += 0.1;
            break;
        case Qt::Key_Minus:
            m_zCamPos -= 0.1;
            break;
        case Qt::Key_Left:
            m_xCamPos -= 0.1;
            break;
        case Qt::Key_Right:
            m_xCamPos += 0.1;
            break;
        case Qt::Key_Up:
            m_yCamPos += 0.1;
            break;
        case Qt::Key_Down:
            m_yCamPos -= 0.1;
            break;
        // Light movement
        case Qt::Key_A:
            m_xLight -= 1;
            break;
        case Qt::Key_D:
            m_xLight += 1;
            break;
        case Qt::Key_S:
            m_yLight -= 1;
            break;
        case Qt::Key_W:
            m_yLight += 1;
            break;
        case Qt::Key_Q:
            m_zLight -= 1;
            break;
        case Qt::Key_E:
            m_zLight += 1;
            break;
        // Reset
        case Qt::Key_Space:
            m_xRot = m_yRot = m_zRot = 0;
            m_xLight = m_yLight = 0;
            m_zLight = 30;
            m_xCamPos = m_yCamPos = 0;
            m_zCamPos = -5;
        default:
            break;
    }
    m_camera.setToIdentity();
    m_camera.translate(-m_xCamPos, -m_yCamPos, m_zCamPos);
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
