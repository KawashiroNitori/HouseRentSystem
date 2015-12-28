#ifndef DIALOGEDITPERSON_H
#define DIALOGEDITPERSON_H

#include <QDialog>
#include "person.h"
#include <QValidator>

namespace Ui {
class DialogEditPerson;
}

class DialogEditPerson : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditPerson(Person** _person,QWidget *parent = 0);
    ~DialogEditPerson();

private slots:
    void on_LineEditID_textChanged(const QString &str);

    void on_lineEditName_textChanged(const QString &str);

    void on_LineEditTel_textChanged(const QString &str);

    void on_LineEditAddr_textEdited(const QString &str);

    void on_buttonBox_accepted();

private:
    Ui::DialogEditPerson *ui;
    Person* person;
    QRegExpValidator* validatorIDPtr;
    QRegExpValidator* validatorTelPtr;
    void tryEnableOK(QString str);
};

#endif // DIALOGEDITPERSON_H
