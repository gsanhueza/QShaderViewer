QT += core gui opengl widgets

TARGET = shaderviewer
TEMPLATE = app

FORMS += src/shaderviewer.ui

SOURCES += src/main.cpp \
    src/shaderviewer.cpp \
    src/oglwidget.cpp

HEADERS += src/shaderviewer.h \
    src/oglwidget.h
