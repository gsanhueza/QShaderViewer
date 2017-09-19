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

#ifndef _SHADERVIEWER_H_
#define _SHADERVIEWER_H_

#include <QDesktopWidget>
#include <QMainWindow>
#include <QFileDialog>
#include "about.h"
#include "model.h"
#include "tutorial.h"

/**
* @brief Namespace used by shaderviewer.ui
*
*/
namespace Ui
{
    class ShaderViewer;
}

/**
* @brief ShaderViewer class. Contains the whole window, menu bar, OGLWidget and status bar.
*
*/
class ShaderViewer : public QMainWindow
{
    Q_OBJECT;

public:
    /**
    * @brief ShaderViewer class constructor.
    *
    * @param model p_model: Model used to load data.
    * @param parent p_parent: Parent of the class. Used by Qt.
    */
    explicit ShaderViewer(Model model, QWidget *parent = nullptr);

    /**
    * @brief ShaderViewer class destructor.
    *
    */
    ~ShaderViewer();

    /**
    * @brief Receptor de teclas pulsadas.
    *
    * @param event p_event: Evento. Ejemplo, Qt::Key_Plus.
    */
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    /**
    * @brief Receiver of a Qt signal when the Load Geometry action is clicked in the window.
    *
    */
    void loadGeometryClicked();

    /**
     * @brief Receiver of a Qt signal when the Load Vertex action is clicked in the window.
     *
     */
    void loadVertexClicked();

    /**
     * @brief Receiver of a Qt signal when the Load Fragment action is clicked in the window.
     *
     */
    void loadFragmentClicked();

    /**
     * @brief Receiver of a Qt signal when the Help -> Tutorial action is clicked in the window.
     *
     */
    void loadTutorialClicked();

    /**
     * @brief Receiver of a Qt signal when the Help -> About action is clicked in the window.
     *
     */
    void loadAboutClicked();

signals:
    /**
     * @brief Emitter of a Qt signal when the model has to be loaded into OGLWidget.
     *
     */
    void emitModel(const Model &m);
    void keyPressed(QKeyEvent *event);

private:
    Ui::ShaderViewer *ui;
    Tutorial *m_tutorial;
    About *m_about;
    Model m_model;
};

#endif
