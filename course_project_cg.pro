#-------------------------------------------------
#
# Project created by QtCreator 2017-10-01T12:39:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = course_project_cg
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/widgets/imageview.cpp \
    src/math/matrix.cpp \
    src/math/image.cpp \
    src/math/rgbimage.cpp \
    src/math/grayscaleimage.cpp \
    src/math/rgbcolor.cpp \
    src/math/grayscalecolor.cpp

HEADERS  += src/mainwindow.h \
    src/widgets/imageview.h \
    src/math/matrix.h \
    src/math/image.h \
    src/math/rgbimage.h \
    src/math/grayscaleimage.h \
    src/math/rgbcolor.h \
    src/math/grayscalecolor.h \
    src/number.h

FORMS    += ui/mainwindow.ui
