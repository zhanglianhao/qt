//#include "mainwindow.h"
#include "analysis.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    analysis w;
    w.show();
    QString url;
    url=argv[1];//arg[0]:程序地址 arg[1]传入启动文件的地址
    if(!url.isNull())
    {
        w.openfile(url,0,0);
    }
    return a.exec();
}
