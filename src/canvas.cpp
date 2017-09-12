#include "canvas.h"
#include "ui_ShaderViewer.h"

ShaderViewer::ShaderViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShaderViewer)
{
    ui->setupUi(this);
}

ShaderViewer::~ShaderViewer()
{
    delete ui;
}
/*
void ShaderViewer::setupUi(QMainWindow *ShaderViewer)
{
    if (ShaderViewer->objectName().isEmpty())
        ShaderViewer->setObjectName(QStringLiteral("ShaderViewer"));
    ShaderViewer->resize(1280, 720);
    actionCargar_Geometria = new QAction(ShaderViewer);
    actionCargar_Geometria->setObjectName(QStringLiteral("actionCargar_Geometria"));
    actionCargar_Vertex = new QAction(ShaderViewer);
    actionCargar_Vertex->setObjectName(QStringLiteral("actionCargar_Vertex"));
    actionCargar_Fragment = new QAction(ShaderViewer);
    actionCargar_Fragment->setObjectName(QStringLiteral("actionCargar_Fragment"));
    actionSalir = new QAction(ShaderViewer);
    actionSalir->setObjectName(QStringLiteral("actionSalir"));
    actionTutorial = new QAction(ShaderViewer);
    actionTutorial->setObjectName(QStringLiteral("actionTutorial"));
    actionAcerca_de = new QAction(ShaderViewer);
    actionAcerca_de->setObjectName(QStringLiteral("actionAcerca_de"));
    centralwidget = new QWidget(ShaderViewer);
    centralwidget->setObjectName(QStringLiteral("centralwidget"));
    gridLayout = new QGridLayout(centralwidget);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    openGLWidget = new QOpenGLWidget(centralwidget);
    openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

    gridLayout->addWidget(openGLWidget, 0, 0, 1, 1);

    ShaderViewer->setCentralWidget(centralwidget);
    menubar = new QMenuBar(ShaderViewer);
    menubar->setObjectName(QStringLiteral("menubar"));
    menubar->setGeometry(QRect(0, 0, 1280, 47));
    menuArchivo = new QMenu(menubar);
    menuArchivo->setObjectName(QStringLiteral("menuArchivo"));
    menuAyuda = new QMenu(menubar);
    menuAyuda->setObjectName(QStringLiteral("menuAyuda"));
    ShaderViewer->setMenuBar(menubar);
    statusbar = new QStatusBar(ShaderViewer);
    statusbar->setObjectName(QStringLiteral("statusbar"));
    ShaderViewer->setStatusBar(statusbar);

    menubar->addAction(menuArchivo->menuAction());
    menubar->addAction(menuAyuda->menuAction());
    menuArchivo->addAction(actionCargar_Geometria);
    menuArchivo->addAction(actionCargar_Vertex);
    menuArchivo->addAction(actionCargar_Fragment);
    menuArchivo->addSeparator();
    menuArchivo->addAction(actionSalir);
    menuAyuda->addAction(actionTutorial);
    menuAyuda->addSeparator();
    menuAyuda->addAction(actionAcerca_de);

    retranslateUi(ShaderViewer);

    QMetaObject::connectSlotsByName(ShaderViewer);
}

void ShaderViewer::retranslateUi(QMainWindow *ShaderViewer)
{
    ShaderViewer->setWindowTitle(QApplication::translate("ShaderViewer", "MainWindow", Q_NULLPTR));
    actionCargar_Geometria->setText(QApplication::translate("ShaderViewer", "&Cargar Geometr\303\255a", Q_NULLPTR));
    actionCargar_Vertex->setText(QApplication::translate("ShaderViewer", "&Cargar Vertex", Q_NULLPTR));
    actionCargar_Fragment->setText(QApplication::translate("ShaderViewer", "&Cargar Fragment", Q_NULLPTR));
    actionSalir->setText(QApplication::translate("ShaderViewer", "&Salir", Q_NULLPTR));
    actionTutorial->setText(QApplication::translate("ShaderViewer", "&Tutorial", Q_NULLPTR));
    actionAcerca_de->setText(QApplication::translate("ShaderViewer", "&Acerca de...", Q_NULLPTR));
    menuArchivo->setTitle(QApplication::translate("ShaderViewer", "Archivo", Q_NULLPTR));
    menuAyuda->setTitle(QApplication::translate("ShaderViewer", "A&yuda", Q_NULLPTR));
}*/
