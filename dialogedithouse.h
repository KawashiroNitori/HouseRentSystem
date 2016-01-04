#ifndef DIALOGEDITHOUSE_H
#define DIALOGEDITHOUSE_H

#include "person.h"
#include "house.h"
#include "dialogeditperson.h"
#include "dialogselectperson.h"
#include "databasemanager.h"
#include <QDialog>

namespace Ui {
class DialogEditHouse;
}

class DialogEditHouse : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditHouse(House **h, QWidget *parent = 0);
    ~DialogEditHouse();

private slots:
    void on_searchButton_clicked();

    void on_createButton_clicked();

    void tryEnableOK();

    void on_buttonBox_accepted();

private:
    Ui::DialogEditHouse *ui;
    House** house;
    Person* person;

};

#endif // DIALOGEDITHOUSE_H
