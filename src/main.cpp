#include "debugmainwindow.h"
#include <QApplication>

#include "src/math/homogeneousvertex.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DebugMainWindow w;
    w.show();
    return a.exec();
}
