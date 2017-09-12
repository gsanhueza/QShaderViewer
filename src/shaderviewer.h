#ifndef _SHADERVIEWER_H_
#define _SHADERVIEWER_H_

#include <QMainWindow>

namespace Ui {
    class ShaderViewer;
}

class ShaderViewer : public QMainWindow
{
    Q_OBJECT;

private:
    Ui::ShaderViewer *ui;

public:
    explicit ShaderViewer(QWidget *parent = nullptr);
    ~ShaderViewer();
};

#endif
