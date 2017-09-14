QT += core gui opengl widgets

TARGET = shaderviewer
TEMPLATE = app

FORMS += shaderviewer.ui

SOURCES += src/main.cpp \
        src/shaderviewer.cpp \
        src/oglwidget.cpp \
        src/model.cpp \
        src/offreader.cpp

HEADERS +=  src/shaderviewer.h \
            src/oglwidget.h \
            src/model.h \
            src/offreader.h

LIBS += -lglut -LGLU
