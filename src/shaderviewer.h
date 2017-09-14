#ifndef _SHADERVIEWER_H_
#define _SHADERVIEWER_H_

#include <QMainWindow>
#include <QFileDialog>
#include "model.h"

namespace Ui {
    class ShaderViewer;
}

class ShaderViewer : public QMainWindow
{
    Q_OBJECT;

public:
    explicit ShaderViewer(Model model, QWidget *parent = nullptr);
    ~ShaderViewer();

public slots:
    void loadGeometryClicked();
    void loadVertexClicked();
    void loadFragmentClicked();

private:
    Ui::ShaderViewer *ui;
    Model m_model;
};

#endif
