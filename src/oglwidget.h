#ifndef _OGLWIDGET_H_
#define _OGLWIDGET_H_

#include <QWidget>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <GL/glu.h>
#include <GL/gl.h>

#include "model.h"

class OGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT;

public:
    OGLWidget(QWidget *parent = nullptr);
    ~OGLWidget();

public slots:
    void receiveModel(const Model &m);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    Model m_model;

    void setupVertexAttribs();

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram *m_program;
    int m_projMatrixLoc;
    int m_mvMatrixLoc;
    int m_normalMatrixLoc;
    int m_lightPosLoc;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;

    QVector<GLfloat> m_data;
};
#endif
