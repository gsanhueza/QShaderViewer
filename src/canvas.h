#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

namespace Ui {
    class ShaderViewer;
}

class ShaderViewer : public QMainWindow
{
    Q_OBJECT;

private:
    QAction *actionCargar_Geometria;
    QAction *actionCargar_Vertex;
    QAction *actionCargar_Fragment;
    QAction *actionSalir;
    QAction *actionTutorial;
    QAction *actionAcerca_de;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QOpenGLWidget *openGLWidget;
    QMenuBar *menubar;
    QMenu *menuArchivo;
    QMenu *menuAyuda;
    QStatusBar *statusbar;

    Ui::ShaderViewer *ui;

public:
    explicit ShaderViewer(QWidget *parent = nullptr);
    ~ShaderViewer();

//     void setupUi(QMainWindow *ShaderViewer);
//     void retranslateUi(QMainWindow *ShaderViewer);
};

#endif
