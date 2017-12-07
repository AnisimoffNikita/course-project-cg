#include "mainwindow.h"
#include "mainwindow.h"
#include <QApplication>
#include <QResource>
#include <QFile>

#include "src/math/homogeneousvertex.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QResource::registerResource("res/models.qrc");
    MainWindow w;
    w.show();
    return a.exec();
}
