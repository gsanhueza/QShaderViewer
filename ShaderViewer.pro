QT += core gui opengl widgets

TARGET = shaderviewer
TEMPLATE = app

FORMS += shaderviewer.ui

SOURCES += src/main.cpp \
        src/shaderviewer.cpp \
        src/oglwidget.cpp

HEADERS += src/shaderviewer.h \
        src/oglwidget.h

LIBS += -lglut -LGLU
