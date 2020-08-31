#include "mainwindow.h"
#include "playerform.h"
#include "alerttable.h"
#include<QThread>
#include <QApplication>
#include<QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AlertTable w;
    w.show();
    PlayerForm p;
    p.show();
    return a.exec();
}
