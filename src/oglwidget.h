#ifndef _OGLWIDGET_H_
#define _OGLWIDGET_H_

#include <QWidget>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QMouseEvent>
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
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Model m_model;

    void setupVertexAttribs();
    void generateGLProgram();
    void cleanup();

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
    QPoint m_lastPos;
    int m_xRot;
    int m_yRot;
    int m_zRot;

    QVector<GLfloat> m_data;
};
#endif
