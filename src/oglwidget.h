/*
 * QShaderViewer is a geometry and shader visualization program.
 * Copyright (C) 2017  Gabriel Sanhueza <gabriel_8032@hotmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
#include <QStringRef>

#include "model.h"

class OGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT;

public:
    OGLWidget(QWidget *parent = nullptr);
    ~OGLWidget();

public slots:
    void receiveModel(const Model &m);
    void keyPressed(QKeyEvent *event);
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
    void loadData();
    void cleanup();

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram *m_program;
    int m_modelViewMatrixLoc;
    int m_projMatrixLoc;

    int m_normalMatrixLoc;
    int m_lightPosLoc;
    int m_eyePosLoc;
    int m_materialLoc;
    int m_albedoLoc;

    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    QPoint m_lastPos;

    int m_xRot;
    int m_yRot;
    int m_zRot;

    int m_xLight;
    int m_yLight;
    int m_zLight;

    float m_xCamPos;
    float m_yCamPos;
    float m_zCamPos;

    QVector<GLfloat> m_data;
    QVector<QVector3D> m_albedoVector;
    QVector<QVector2D> m_materialVector;
    int m_materialPos;
    bool m_dataAlreadyLoaded;
};
#endif
