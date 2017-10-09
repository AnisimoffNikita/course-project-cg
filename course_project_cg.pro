#-------------------------------------------------
#
# Project created by QtCreator 2017-10-01T12:39:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = course_project_cg
TEMPLATE = app
CONFIG += c++14

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
    src/image/image.cpp \
    src/image/color.cpp \
    src/image/imageconverter.cpp \
    src/algorithm/edgedetector.cpp \
    src/algorithm/linetransform.cpp \
    src/algorithm/cannyedgedetector.cpp \
    src/algorithm/imageprocessor.cpp \
    src/algorithm/grayscaleconverter.cpp \
    src/math/math.cpp

HEADERS  += src/mainwindow.h \
    src/widgets/imageview.h \
    src/math/matrix.h \
    src/image/image.h \
    src/number.h \
    src/image/color.h \
    src/image/imageconverter.h \
    src/algorithm/edgedetector.h \
    src/algorithm/linetransform.h \
    src/algorithm/cannyedgedetector.h \
    src/algorithm/imageprocessor.h \
    src/algorithm/grayscaleconverter.h \
    src/math/math.h

FORMS    += ui/mainwindow.ui
