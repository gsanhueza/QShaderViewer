QT += core gui opengl widgets

TARGET = shaderviewer
TEMPLATE = app

FORMS += shaderviewer.ui

SOURCES += src/main.cpp \
        src/shaderviewer.cpp \
        src/oglwidget.cpp \
        src/model.cpp \
        src/geometryreader.cpp

HEADERS +=  src/shaderviewer.h \
            src/oglwidget.h \
            src/model.h \
            src/geometryreader.h

LIBS += -lglut -LGLU
