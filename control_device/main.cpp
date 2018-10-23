#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    algorithm_file w;
    w.show();
    return a.exec();
}
