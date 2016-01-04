#include "mainwindow.h"
#include "house.h"
#include "person.h"
#include "contract.h"
#include "dialogeditperson.h"
#include "dialogselectperson.h"
#include "dialogedithouse.h"
#include "dialogselecthouse.h"
#include "dialogeditcontract.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DatabaseManager::getInstance();
    //Person* person=NULL;
    //DialogEditPerson p(&person,&w);
    //p.exec();
    //DialogSelectPerson s(&person,&w);
    //s.exec();
    /*
    House* house=NULL;
    DialogEditHouse h(&house,&w);
    h.exec();
    DialogEditHouse h1(&house,&w);
    h1.exec();
    */
    //DialogSelectHouse h(&house,&w);
    //h.exec();
    /*
    Contract* contract=NULL;
    DialogEditContract c(&contract,&w);
    c.exec();
    DialogEditContract c1(&contract,&w);
    c1.exec();*/

    //QMessageBox::information(&w,"info",house->getID());
    return a.exec();
}
