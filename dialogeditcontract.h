#ifndef DIALOGEDITCONTRACT_H
#define DIALOGEDITCONTRACT_H

#include <QDialog>
#include "databasemanager.h"
#include "dialogedithouse.h"
#include "dialogeditperson.h"
#include "dialogselecthouse.h"
#include "dialogselectperson.h"
#include "contract.h"
#include "house.h"
#include "person.h"

namespace Ui {
class DialogEditContract;
}

class DialogEditContract : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditContract(Contract **c, QWidget *parent = 0);
    ~DialogEditContract();

private slots:
    void tryEnableOK();

    void on_DateEditStart_dateChanged(const QDate &date);

    void on_DateEditEnd_dateChanged(const QDate &date);

    void on_searchHolderButton_clicked();

    void on_createPersonButton_clicked();

    void on_searchHouseButton_clicked();

    void on_createHouseButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogEditContract *ui;
    Contract** contract;
    House* house;
    Person* person;

};

#endif // DIALOGEDITCONTRACT_H
