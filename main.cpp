#include "mainwindow.h"
#include "house.h"
#include "person.h"
#include "contract.h"
#include "configmanager.h"
#include "dialogeditperson.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Person* person=NULL;
    DialogEditPerson p(&person,&w);
    p.exec();

    return a.exec();
}
