#pragma execution_character_set("utf-8")

#include "dialogeditperson.h"
#include "ui_dialogeditperson.h"
#include "person.h"
#include "databasemanager.h"
#include <Qt>
#include <QPushButton>
#include <QMessageBox>

DialogEditPerson::DialogEditPerson(Person** _person, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditPerson),
    person(_person)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::WindowCloseButtonHint);
    setFixedSize(size());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDefault(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(QString("确定"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(QString("取消"));
    validatorIDPtr=new QRegExpValidator(QRegExp("[1-9]\\d{5}[1-9]\\d{3}((0\\d)|(1[0-2]))(([0|1|2]\\d)|3[0-1])\\d{3}([0-9]|X)"),ui->LineEditID);
    ui->LineEditID->setValidator(validatorIDPtr);
    validatorTelPtr=new QRegExpValidator(QRegExp("(\\d{11})|^((\\d{7,8})|(\\d{4}|\\d{3})-(\\d{7,8})|(\\d{4}|\\d{3})-(\\d{7,8})-(\\d{4}|\\d{3}|\\d{2}|\\d{1})|(\\d{7,8})-(\\d{4}|\\d{3}|\\d{2}|\\d{1}))"),ui->LineEditTel);
    ui->LineEditTel->setValidator(validatorTelPtr);
    if (person && *person)
    {
        setWindowTitle("编辑个人");
        ui->LineEditID->setText((*person)->getID());
        ui->lineEditName->setText((*person)->getName());
        ui->LineEditAddr->setText((*person)->getAddress());
        ui->LineEditTel->setText((*person)->getTel());
        on_LineEditID_textChanged((*person)->getID());
        ui->LineEditID->setReadOnly(true);
    }
    else
    {
        setWindowTitle("创建个人");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

DialogEditPerson::~DialogEditPerson()
{
    delete validatorIDPtr;
    delete validatorTelPtr;
    delete ui;
}

void DialogEditPerson::tryEnableOK(QString str)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(Person::isIDValid(ui->LineEditID->text().toStdString()) &&
                                                                ui->lineEditName->text().length()>0 &&
                                                                ui->LineEditAddr->text().length()>0 &&
                                                                ui->LineEditTel->text().length()>0 &&
                                                                str.length()>0);
}

void DialogEditPerson::on_LineEditID_textChanged(const QString &str)
{
    int pos=ui->LineEditID->cursorPosition();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    if (str.length()!=18)
    {
        ui->LineEditAge->clear();
        ui->LineEditBirthday->clear();
        ui->LineEditSex->clear();
        return;
    }
    if (validatorIDPtr->validate((QString)str,pos)!=QValidator::Acceptable || !Person::isIDValid(str.toStdString()))
        return;
    Person tempP(str,ui->lineEditName->text(),ui->LineEditAddr->text(),ui->LineEditTel->text());
    if (!tempP.getBirthday().isValid())
        return;
    ui->LineEditAge->setText(QString::number(tempP.getAge()));
    ui->LineEditBirthday->setText(tempP.getBirthday().toString(Qt::ISODate));
    ui->LineEditSex->setText(tempP.getSex()?QString("男"):QString("女"));
    tryEnableOK(str);

}

void DialogEditPerson::on_lineEditName_textChanged(const QString &str)
{
    tryEnableOK(str);
}

void DialogEditPerson::on_LineEditTel_textChanged(const QString &str)
{
    tryEnableOK(str);
}

void DialogEditPerson::on_LineEditAddr_textEdited(const QString &str)
{
    tryEnableOK(str);
}

void DialogEditPerson::on_buttonBox_accepted()
{
    if (!person)
        return;

    if (this->windowTitle()=="添加个人" && DatabaseManager::getInstance().isPersonIDExisted(ui->LineEditID->text()))
    {
        QMessageBox::critical(this,"错误","当前已存在相同的身份证号。");
        return;
    }

    if (!*person)
        *person=new Person(ui->LineEditID->text(),ui->lineEditName->text(),ui->LineEditAddr->text(),ui->LineEditTel->text());
    else
        **person=Person(ui->LineEditID->text(),ui->lineEditName->text(),ui->LineEditAddr->text(),ui->LineEditTel->text());
    this->accept();
}
