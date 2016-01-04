#include "dialogeditcontract.h"
#include "ui_dialogeditcontract.h"

DialogEditContract::DialogEditContract(Contract** c,QWidget *parent) :
    QDialog(parent),
    contract(c),
    house(NULL),
    person(NULL),
    ui(new Ui::DialogEditContract)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::WindowCloseButtonHint);
    setFixedSize(size());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDefault(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(QString("确定"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(QString("取消"));

    ui->DateEditStart->setDate(QDate::currentDate());
    ui->DateEditEnd->setDate(QDate::currentDate().addMonths(1));
    ui->DateEditStart->setMaximumDate(ui->DateEditEnd->date().addDays(-1));
    if (contract && *contract)
    {
        setWindowTitle("编辑合同");
        ui->LineEditID->setText((**contract).getID());
        person=new Person((*contract)->getHolder());
        ui->labelHolderID->setText(person->getID());
        ui->labelHolderName->setText(person->getName());
        house=new House((*contract)->getHouse());
        ui->labelHouseID->setText(house->getID());
        ui->labelHouseAddr->setText(house->getAddress());
        ui->DateEditStart->setDate((*contract)->getStartDate());
        ui->DateEditEnd->setDate((*contract)->getEndDate());
        ui->SpinBoxRent->setValue((*contract)->getRent());
        ui->textEdit->setText((*contract)->getRemark());
        if ((*contract)->getEndDate()<QDate::currentDate())
            ui->DateEditEnd->setMinimumDate((*contract)->getEndDate());
        else
            ui->DateEditEnd->setMinimumDate(QDate::currentDate());

    }
    else
    {
        setWindowTitle("创建合同");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->LineEditID->setText(DatabaseManager::getInstance().getNewContractID());
        ui->DateEditEnd->setMinimumDate(QDate::currentDate());
    }
}

DialogEditContract::~DialogEditContract()
{
    if (person)
        delete person;
    if (house)
        delete house;
    delete ui;
}

void DialogEditContract::tryEnableOK()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(person && house);
}

void DialogEditContract::on_DateEditStart_dateChanged(const QDate &date)
{
    ui->DateEditEnd->setMinimumDate(date.addDays(1)<QDate::currentDate()?QDate::currentDate():date.addDays(1));
}

void DialogEditContract::on_DateEditEnd_dateChanged(const QDate &date)
{
    ui->DateEditStart->setMaximumDate(date.addDays(-1));
}

void DialogEditContract::on_searchHolderButton_clicked()
{
    Person* temp=NULL;
    DialogSelectPerson p(&temp,this);
    p.exec();
    if (temp)
    {
        delete person;
        person=temp;
        ui->labelHolderID->setText(person->getID());
        ui->labelHolderName->setText(person->getName());
    }
    tryEnableOK();
}

void DialogEditContract::on_createPersonButton_clicked()
{
    Person* temp=NULL;
    DialogEditPerson p(&temp,this);
    p.exec();
    if (temp)
    {
        delete person;
        person=temp;
        ui->labelHolderID->setText(person->getID());
        ui->labelHolderName->setText(person->getName());
    }
    tryEnableOK();
}

void DialogEditContract::on_searchHouseButton_clicked()
{
    House* temp=NULL;
    DialogSelectHouse h(&temp,this);
    h.exec();
    if (temp)
    {
        delete house;
        house=temp;
        ui->labelHouseID->setText(house->getID());
        ui->labelHouseAddr->setText(house->getAddress());
    }
    tryEnableOK();
}

void DialogEditContract::on_createHouseButton_clicked()
{
    House* temp=NULL;
    DialogEditHouse h(&temp,this);
    h.exec();
    if (temp)
    {
        delete house;
        house=temp;
        ui->labelHouseID->setText(house->getID());
        ui->labelHouseAddr->setText(house->getAddress());
    }
    tryEnableOK();
}

void DialogEditContract::on_buttonBox_accepted()
{
    if (!contract)
        return;

    if (!*contract)
        *contract=new Contract(ui->LineEditID->text(),*person,*house,ui->DateEditStart->date(),ui->DateEditEnd->date(),ui->SpinBoxRent->value(),ui->textEdit->toPlainText());
    else
        **contract=Contract(ui->LineEditID->text(),*person,*house,ui->DateEditStart->date(),ui->DateEditEnd->date(),ui->SpinBoxRent->value(),ui->textEdit->toPlainText());
}
