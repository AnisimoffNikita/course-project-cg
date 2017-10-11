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
    src/algorithm/edgedetector/edgedetector.cpp \
    src/algorithm/linetransform/linetransform.cpp \
    src/algorithm/edgedetector/cannyedgedetector.cpp \
    src/math/math.cpp \
    src/image/grayscaleimage.cpp \
    src/image/imagebase.cpp \
    src/image/grayscalecolor.cpp \
    src/algorithm/linetransform/houghtransform.cpp \
    src/math/point.cpp \
    src/math/line.cpp \
    src/algorithm/blur/gaussianblur.cpp \
    src/math/cylindersize.cpp \
    src/algorithm/cylindersizecalculator.cpp \
    src/algorithm/cylindersizecalculatorbase.cpp \
    src/algorithm/blur/blur.cpp

HEADERS  += src/mainwindow.h \
    src/widgets/imageview.h \
    src/math/matrix.h \
    src/image/image.h \
    src/number.h \
    src/image/color.h \
    src/image/imageconverter.h \
    src/algorithm/edgedetector/edgedetector.h \
    src/algorithm/linetransform/linetransform.h \
    src/algorithm/edgedetector/cannyedgedetector.h \
    src/math/math.h \
    src/image/grayscaleimage.h \
    src/image/imagebase.h \
    src/image/grayscalecolor.h \
    src/algorithm/linetransform/houghtransform.h \
    src/math/point.h \
    src/math/line.h \
    src/algorithm/blur/gaussianblur.h \
    src/math/cylindersize.h \
    src/algorithm/cylindersizecalculator.h \
    src/algorithm/cylindersizecalculatorbase.h \
    src/algorithm/blur/blur.h

FORMS    += ui/mainwindow.ui
QMAKE_CXXFLAGS_RELEASE += -O3
