#include "MiniCAD.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MiniCAD w;
    w.show();
    return a.exec();
}
