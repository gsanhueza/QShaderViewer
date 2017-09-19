QT += core gui opengl widgets

TARGET   = qshaderviewer
TEMPLATE = app

FORMS   +=  qshaderviewer.ui \
            tutorial.ui \
            about.ui

SOURCES +=  src/main.cpp \
            src/qshaderviewer.cpp \
            src/oglwidget.cpp \
            src/model.cpp \
            src/geometryreader.cpp \
            src/tutorial.cpp \
            src/about.cpp \

HEADERS +=  src/qshaderviewer.h \
            src/oglwidget.h \
            src/model.h \
            src/geometryreader.h \
            src/tutorial.h \
            src/about.h \

LIBS    += -lglut -LGLU
