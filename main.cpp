#include "mainwindow.h"
#include "house.h"
#include "person.h"
#include "contract.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Person p("210102199601316616","li","10-1",18524431702);
    w.show();

    return a.exec();
}
