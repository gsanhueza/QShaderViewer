#ifndef _OGLWIDGET_H_
#define _OGLWIDGET_H_

#include <QWidget>
#include <QOpenGLWidget>
#include <GL/glu.h>
#include <GL/gl.h>

#include "model.h"

class OGLWidget : public QOpenGLWidget
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
};
#endif
