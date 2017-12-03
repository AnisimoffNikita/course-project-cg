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
##QMAKE_LIBS+=-lgomp -lpthread
#MAKE_CXXFLAGS+=-O3

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
    src/math/line.cpp \
    src/algorithm/blur/gaussianblur.cpp \
    src/math/cylindersize.cpp \
    src/algorithm/cylindersizecalculator.cpp \
    src/algorithm/cylindersizecalculatorbase.cpp \
    src/algorithm/blur/blur.cpp \
    src/widgets/modelview.cpp \
    src/animation/sceneobject.cpp \
    src/animation/model.cpp \
    src/animation/camera.cpp \
    src/animation/light.cpp \
    src/animation/mesh.cpp \
    src/math/vec2.cpp \
    src/math/vec3.cpp \
    src/math/homogeneousvertex.cpp \
    src/animation/transformation.cpp \
    src/animation/composite.cpp \
    src/animation/scene.cpp \
    src/animation/movetransformation.cpp \
    src/animation/scaletransformation.cpp \
    src/animation/rotatetransform.cpp \
    src/animation/matrixfactory.cpp \
    src/animation/commontransformation.cpp \
    src/animation/sceneobjectfactory.cpp \
    src/animation/meshgenerator.cpp \
    src/animation/renderer.cpp \
    src/animation/meshdata.cpp \
    src/animation/ambientlight.cpp \
    src/animation/pointlight.cpp \
    src/animation/zbuffer.cpp \
    src/animation/lightzbufferrenderer.cpp \
    src/animation/objloader.cpp \
    src/widgets/modelview2.cpp \
    src/animation/actionmanager.cpp \
    src/animation/actions.cpp

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
    src/math/line.h \
    src/algorithm/blur/gaussianblur.h \
    src/math/cylindersize.h \
    src/algorithm/cylindersizecalculator.h \
    src/algorithm/cylindersizecalculatorbase.h \
    src/algorithm/blur/blur.h \
    src/widgets/modelview.h \
    src/animation/sceneobject.h \
    src/animation/model.h \
    src/animation/camera.h \
    src/animation/light.h \
    src/animation/mesh.h \
    src/math/vec2.h \
    src/math/vec3.h \
    src/math/homogeneousvertex.h \
    src/animation/transformation.h \
    src/animation/composite.h \
    src/animation/scene.h \
    src/animation/movetransformation.h \
    src/animation/scaletransformation.h \
    src/animation/rotatetransform.h \
    src/animation/matrixfactory.h \
    src/animation/commontransformation.h \
    src/animation/sceneobjectfactory.h \
    src/animation/meshgenerator.h \
    src/animation/renderer.h \
    src/animation/meshdata.h \
    src/animation/ambientlight.h \
    src/animation/pointlight.h \
    src/animation/zbuffer.h \
    src/animation/lightzbufferrenderer.h \
    src/animation/objloader.h \
    src/3rdparty/ObjLoader/objloader.h \
    src/widgets/modelview2.h \
    src/animation/actionmanager.h \
    src/animation/actions.h

SUBDIRS += src

FORMS    += ui/mainwindow.ui
QMAKE_CXXFLAGS_RELEASE += -O3
