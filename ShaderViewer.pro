QT += core gui opengl widgets

TARGET   = shaderviewer
TEMPLATE = app

FORMS   +=  shaderviewer.ui \
            tutorial.ui \
            about.ui

SOURCES +=  src/main.cpp \
            src/shaderviewer.cpp \
            src/oglwidget.cpp \
            src/model.cpp \
            src/geometryreader.cpp \
            src/tutorial.cpp \
            src/about.cpp

HEADERS +=  src/shaderviewer.h \
            src/oglwidget.h \
            src/model.h \
            src/geometryreader.h \
            src/tutorial.h \
            src/about.h

LIBS    += -lglut -LGLU
