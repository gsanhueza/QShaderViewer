#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget* parent)
    : QOpenGLWidget(parent),
      m_program(0)
{
}

OGLWidget::~OGLWidget()
{
}

static const char *vertexShaderSource =
"attribute vec4 vertex;\n"
"attribute vec3 normal;\n"
"varying vec3 vert;\n"
"varying vec3 vertNormal;\n"
"uniform mat4 projMatrix;\n"
"uniform mat4 mvMatrix;\n"
"uniform mat3 normalMatrix;\n"
"void main() {\n"
"   vert = vertex.xyz;\n"
"   vertNormal = normalMatrix * normal;\n"
// "   gl_Position = projMatrix * mvMatrix * vertex;\n"
"   gl_Position = vertex;\n"
"}\n";

static const char *fragmentShaderSource =
"varying highp vec3 vert;\n"
"varying highp vec3 vertNormal;\n"
"uniform highp vec3 lightPos;\n"
"void main() {\n"
"   highp vec3 L = normalize(lightPos - vert);\n"
"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
"   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
"   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
"   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
// "   gl_FragColor = vec4(col, 1.0);\n"
"}\n";

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

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
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

//     // Setup our vertex buffer object.
//     m_vbo.create();
//     m_vbo.bind();
//
// //     FIXME Parece que aquí se ponen los vértices de mi polígono
//     m_data.append(QVector<GLfloat>
//     { -1, 0, 0,
//         0,  0, 0,
//         1, -1, 0 });
// //     FIXME Esto no debería estar en initializeGL, sino que en paintGL
// //     for (vector<float> point : m_model.getCoordinates())
// //     {
// //         m_data.append(static_cast<float>(point.at(0)) / 100);
// //         m_data.append(static_cast<float>(point.at(1)) / 100);
// //         m_data.append(static_cast<float>(point.at(2)) / 100);
// //     }
//
//     m_vbo.allocate(m_data.constData(), m_data.count() * sizeof(GLfloat));
//
//     // Store the vertex attribute bindings for the program.
//     setupVertexAttribs();

    // Our camera never changes in this example.
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -1);

    // Light position is fixed.
    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_program->release();
}

void OGLWidget::paintGL()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_world.setToIdentity();
    int m_xRot = 0;
    int m_yRot = 0;
    int m_zRot = 0;
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

    srand(time(0));
    int r = rand() % 1000;

    m_data.clear();
    cout << "test" << r << endl;
    if (r % 2)
    {
        m_data.append(QVector<GLfloat>{-1, -1, 0});
        m_data.append(QVector<GLfloat>{0, 0.8, 0});
        m_data.append(QVector<GLfloat>{1, -1, 0});
    }
    else
    {
        m_data.append(QVector<GLfloat>{1, 1, 0});
        m_data.append(QVector<GLfloat>{0, -0.8, 0});
        m_data.append(QVector<GLfloat>{-1, 1, 0});
    }

//     FIXME Parece que aquí se ponen los vértices de mi polígono
//     FIXME Deberíamos llamar a update solo cuando se emite la señal recibida por este SLOT
//     m_data.append(QVector<GLfloat>
//     { -1, -1, 0,
//         0, (static_cast<float>(rand()) / RAND_MAX), 0,
//         1, -1, 0 });

//     for (vector<float> point : m_model.getCoordinates())
//     {
//         m_data.append(static_cast<float>(point.at(0)) / 100);
//         m_data.append(static_cast<float>(point.at(1)) / 100);
//         m_data.append(static_cast<float>(point.at(2)) / 100);
//
//         std::cout << static_cast<float>(point.at(0)) / 100 << std::endl;
//     }

    m_vbo.allocate(m_data.constData(), m_data.count() * sizeof(GLfloat));

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();

    glDrawArrays(GL_TRIANGLES, 0, m_data.count() / 3);

    m_program->release();
    update();
}

void OGLWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void OGLWidget::receiveModel(const Model &m)
{
    std::cout << "OGLWIDGET: Recibiendo señal" << std::endl;
    m_model = m;
}
