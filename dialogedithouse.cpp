#include "dialogedithouse.h"
#include "ui_dialogedithouse.h"

DialogEditHouse::DialogEditHouse(House** h,QWidget *parent) :
    QDialog(parent),\
    person(NULL),
    house(h),
    ui(new Ui::DialogEditHouse)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::WindowCloseButtonHint);
    setFixedSize(size());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDefault(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(QString("确定"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(QString("取消"));
    if (house && *house)
    {
        setWindowTitle("编辑房屋");
        ui->LineEditID->setText((*house)->getID());
        person=new Person((*house)->getOwner());
        ui->labelOwnerID->setText(person->getID());
        ui->labelOwnerName->setText(person->getName());
        ui->LineEditAddr->setText((*house)->getAddress());
        ui->doubleSpinBox->setValue((*house)->getSquare());
        ui->LineEditType->setText((*house)->getType());
        ui->textEdit->setText((*house)->getRemark());
    }
    else
    {
        setWindowTitle("创建房屋");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->LineEditID->setText(DatabaseManager::getInstance().getNewHouseID());
    }

    connect(ui->LineEditAddr,SIGNAL(textChanged(QString)),this,SLOT(tryEnableOK()));
    connect(ui->LineEditType,SIGNAL(textChanged(QString)),this,SLOT(tryEnableOK()));
    connect(ui->doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(tryEnableOK()));
}

DialogEditHouse::~DialogEditHouse()
{
    if (person)
        delete person;
    delete ui;
}

void DialogEditHouse::on_searchButton_clicked()
{
    Person* temp=NULL;
    DialogSelectPerson p(&temp,this);
    p.exec();
    if (temp)
    {
        delete person;
        person=temp;
        ui->labelOwnerID->setText(person->getID());
        ui->labelOwnerName->setText(person->getName());
    }
    tryEnableOK();
}

void DialogEditHouse::on_createButton_clicked()
{
    Person* temp=NULL;
    DialogEditPerson p(&temp,this);
    p.exec();
    if (temp)
    {
        delete person;
        person=temp;
        ui->labelOwnerID->setText(person->getID());
        ui->labelOwnerName->setText(person->getName());
    }
    tryEnableOK();
}

void DialogEditHouse::tryEnableOK()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ui->LineEditAddr->text().length()>0 &&
                                                            ui->doubleSpinBox->value()>0.0 &&
                                                            ui->LineEditType->text().length()>0 &&
                                                            person);
}

void DialogEditHouse::on_buttonBox_accepted()
{
    if (!house)
        return;

    if (!*house)
        *house=new House(ui->LineEditID->text(),*person,ui->LineEditAddr->text(),ui->doubleSpinBox->value(),ui->LineEditType->text(),ui->textEdit->toPlainText());
    else
        **house=House(ui->LineEditID->text(),*person,ui->LineEditAddr->text(),ui->doubleSpinBox->value(),ui->LineEditType->text(),ui->textEdit->toPlainText());
}
