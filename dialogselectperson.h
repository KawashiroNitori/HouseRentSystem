#ifndef DIALOGSELECTPERSON_H
#define DIALOGSELECTPERSON_H

#include <QDialog>
#include <QtSql/QtSql>
#include "person.h"

namespace Ui {
class DialogSelectPerson;
}

class DialogSelectPerson : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSelectPerson(Person** _person,QWidget *parent = 0);
    ~DialogSelectPerson();

private slots:
    void on_searchButton_clicked();

    void on_lineEdit_textEdited(const QString &str);

    void on_tableView_clicked(const QModelIndex &index);

    void on_buttonBox_accepted();

    void on_seeAllButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::DialogSelectPerson *ui;
    Person** person;
    QSqlQueryModel* model;
    QModelIndex currentIndex;
};

#endif // DIALOGSELECTPERSON_H
