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
    DatabaseManager::getInstance();
    MainWindow w;
    w.show();

    return a.exec();
}
