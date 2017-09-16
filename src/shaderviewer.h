#ifndef _SHADERVIEWER_H_
#define _SHADERVIEWER_H_

#include <QMainWindow>
#include <QFileDialog>
#include "model.h"

/**
* @brief Namespace used by shaderviewer.ui
*
*/
namespace Ui {
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

private:
    Ui::ShaderViewer *ui;
    Model m_model;
};

#endif
