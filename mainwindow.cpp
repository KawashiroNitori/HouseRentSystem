#pragma execution_character_set("utf-8")

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogeditcontract.h"
#include "dialogedithouse.h"
#include "dialogeditperson.h"
#include <Windows.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    lastContractStr(""),
    lastHouseStr(""),
    lastPersonStr(""),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->lineEditContract,SIGNAL(textChanged(QString)),this,SLOT(tryEnableSearchButton()));
    connect(ui->lineEditHouse,SIGNAL(textChanged(QString)),this,SLOT(tryEnableSearchButton()));
    connect(ui->lineEditPerson,SIGNAL(textChanged(QString)),this,SLOT(tryEnableSearchButton()));

    refreshContractTable();
    refreshHouseTable();
    refreshPersonTable();

    ui->tableViewPerson->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewPerson->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewPerson->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewHouse->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewHouse->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewHouse->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewContract->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewContract->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewContract->setSelectionMode(QAbstractItemView::SingleSelection);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tryEnableSearchButton()
{
    ui->searchContractButton->setEnabled(ui->lineEditContract->text().length()>0);
    ui->searchHouseButton->setEnabled(ui->lineEditHouse->text().length()>0);
    ui->searchPersonButton->setEnabled(ui->lineEditPerson->text().length()>0);
}

void MainWindow::refreshContractTable()
{
    QTableView* table=ui->tableViewContract;
    QSqlQueryModel* model=NULL;
    if (lastContractStr!="")
        model=DatabaseManager::getInstance().searchContract(lastContractStr);
    else
        model=DatabaseManager::getInstance().allContract(false);

    contractModel=model;
    table->setModel(model);
    table->hideColumn(6);
    table->resizeColumnsToContents();
    table->horizontalHeader()->setStretchLastSection(true);

    ui->editContractButton->setEnabled(false);
    ui->deleteContractButton->setEnabled(false);
}

void MainWindow::refreshHouseTable()
{
    QTableView* table=ui->tableViewHouse;
    QSqlQueryModel* model=NULL;
    if (lastHouseStr!="")
        model=DatabaseManager::getInstance().searchHouse(lastHouseStr);
    else
        model=DatabaseManager::getInstance().allHouse(false);

    houseModel=model;
    table->setModel(model);
    table->hideColumn(5);
    table->resizeColumnsToContents();
    table->horizontalHeader()->setStretchLastSection(true);

    ui->editHouseButton->setEnabled(false);
    ui->deleteHouseButton->setEnabled(false);
}

void MainWindow::refreshPersonTable()
{
    QTableView* table=ui->tableViewPerson;
    QSqlQueryModel* model=NULL;
    if (lastPersonStr!="")
        model=DatabaseManager::getInstance().searchPerson(lastPersonStr);
    else
        model=DatabaseManager::getInstance().allPerson(false);

    personModel=model;
    table->setModel(model);
    table->resizeColumnsToContents();
    table->horizontalHeader()->setStretchLastSection(true);

    ui->editPersonButton->setEnabled(false);
    ui->deletePersonButton->setEnabled(false);
}

void MainWindow::on_searchContractButton_clicked()
{
    lastContractStr=ui->lineEditContract->text();
    refreshContractTable();
}

void MainWindow::on_allContractButton_clicked()
{
    lastContractStr="";
    refreshContractTable();
}

void MainWindow::on_searchHouseButton_clicked()
{
    lastHouseStr=ui->lineEditHouse->text();
    refreshHouseTable();
}

void MainWindow::on_allHouseButton_clicked()
{
    lastHouseStr="";
    refreshHouseTable();
}

void MainWindow::on_searchPersonButton_clicked()
{
    lastPersonStr=ui->lineEditPerson->text();
    refreshPersonTable();
}

void MainWindow::on_allPersonButton_clicked()
{
    lastPersonStr="";
    refreshPersonTable();
}

void MainWindow::on_tableViewContract_clicked(const QModelIndex &index)
{
    currentContractIndex=index;
    ui->editContractButton->setEnabled(true);
    ui->deleteContractButton->setEnabled(true);
}

void MainWindow::on_tableViewHouse_clicked(const QModelIndex &index)
{
    currentHouseIndex=index;
    ui->editHouseButton->setEnabled(true);
    ui->deleteHouseButton->setEnabled(true);
}

void MainWindow::on_tableViewPerson_clicked(const QModelIndex &index)
{
    currentPersonIndex=index;
    ui->editPersonButton->setEnabled(true);
    ui->deletePersonButton->setEnabled(true);
}

void MainWindow::on_addContractButton_clicked()
{
    Contract* tempContract=NULL;
    DialogEditContract editContract(&tempContract,this);
    editContract.exec();

    if (tempContract)
    {
        if (!DatabaseManager::getInstance().isPersonIDExisted(tempContract->getHolder().getID()))
            DatabaseManager::getInstance().insertPerson(tempContract->getHolder());
        if (!DatabaseManager::getInstance().isPersonIDExisted(tempContract->getOwner().getID()))
            DatabaseManager::getInstance().insertPerson(tempContract->getOwner());
        if (!DatabaseManager::getInstance().isHouseIDExisted(tempContract->getHouse().getID()))
            DatabaseManager::getInstance().insertHouse(tempContract->getHouse());

        DatabaseManager::getInstance().insertContract(*tempContract);
        refreshContractTable();
        refreshHouseTable();
        refreshPersonTable();

        delete tempContract;
    }
}

void MainWindow::on_addHouseButton_clicked()
{
    House* tempHouse=NULL;
    DialogEditHouse editHouse(&tempHouse,this);
    editHouse.exec();

    if (tempHouse)
    {
        if (!DatabaseManager::getInstance().isPersonIDExisted(tempHouse->getOwner().getID()))
            DatabaseManager::getInstance().insertPerson(tempHouse->getOwner());

        DatabaseManager::getInstance().insertHouse(*tempHouse);
        refreshHouseTable();
        refreshPersonTable();

        delete tempHouse;
    }
}

void MainWindow::on_addPersonButton_clicked()
{
    Person* tempPerson=NULL;
    DialogEditPerson editPerson(&tempPerson,this);
    editPerson.exec();

    if (tempPerson)
    {
        DatabaseManager::getInstance().insertPerson(*tempPerson);
        refreshPersonTable();

        delete tempPerson;
    }
}


void MainWindow::on_editContractButton_clicked()
{
    Contract* tempContract=new Contract(DatabaseManager::getInstance().buildContract(contractModel->record(currentContractIndex.row()).value("id").toString()));

    if (tempContract->getEndDate()<QDate::currentDate())
    {
        QMessageBox::critical(this,"错误","该合同已过期，无法编辑。");
        delete tempContract;
        return;
    }

    DialogEditContract editContract(&tempContract,this);
    editContract.exec();

    if (editContract.result()==QDialog::Accepted)
    {
        if (!DatabaseManager::getInstance().isPersonIDExisted(tempContract->getHolder().getID()))
            DatabaseManager::getInstance().insertPerson(tempContract->getHolder());
        if (!DatabaseManager::getInstance().isPersonIDExisted(tempContract->getOwner().getID()))
            DatabaseManager::getInstance().insertPerson(tempContract->getOwner());
        if (!DatabaseManager::getInstance().isHouseIDExisted(tempContract->getHouse().getID()))
            DatabaseManager::getInstance().insertHouse(tempContract->getHouse());

        DatabaseManager::getInstance().updateContract(*tempContract);
        refreshContractTable();
        refreshHouseTable();
        refreshPersonTable();
    }

    delete tempContract;
}



void MainWindow::on_editHouseButton_clicked()
{
    House* tempHouse=new House(DatabaseManager::getInstance().buildHouse(houseModel->record(currentHouseIndex.row()).value("id").toString()));
    DialogEditHouse editHouse(&tempHouse,this);
    editHouse.exec();

    if (editHouse.result()==QDialog::Accepted)
    {
        if (!DatabaseManager::getInstance().isPersonIDExisted(tempHouse->getOwner().getID()))
            DatabaseManager::getInstance().insertPerson(tempHouse->getOwner());

        DatabaseManager::getInstance().updateHouse(*tempHouse);
        refreshHouseTable();
        refreshPersonTable();
    }

    delete tempHouse;
}

void MainWindow::on_editPersonButton_clicked()
{
    Person* tempPerson=new Person(DatabaseManager::getInstance().buildPerson(personModel->record(currentPersonIndex.row()).value("id").toString()));

    DialogEditPerson editPerson(&tempPerson,this);
    editPerson.exec();

    if (editPerson.result()==QDialog::Accepted)
    {
        DatabaseManager::getInstance().updatePerson(*tempPerson);
        refreshPersonTable();
    }

    delete tempPerson;
}

void MainWindow::on_deleteContractButton_clicked()
{
    if (QMessageBox::warning(this,"警告","删除记录后将无法恢复，确定吗？",QMessageBox::Ok,QMessageBox::Cancel|QMessageBox::Default)==QMessageBox::Ok)
    {
        DatabaseManager::getInstance().deleteContract(contractModel->record(currentContractIndex.row()).value("id").toString());
        refreshContractTable();
    }
}

void MainWindow::on_deleteHouseButton_clicked()
{
    QString houseID=houseModel->record(currentHouseIndex.row()).value("id").toString();
    if (!DatabaseManager::getInstance().canHouseDelete(houseID))
    {
        QMessageBox::critical(this,"错误","存在包含该房屋的合同，无法删除。");
        return;
    }

    if (QMessageBox::warning(this,"警告","删除记录后将无法恢复，确定吗？",QMessageBox::Ok,QMessageBox::Cancel|QMessageBox::Default)==QMessageBox::Ok)
    {
        DatabaseManager::getInstance().deleteHouse(houseID);
        refreshHouseTable();
    }
}

void MainWindow::on_deletePersonButton_clicked()
{
    QString personID=personModel->record(currentPersonIndex.row()).value("id").toString();
    if (!DatabaseManager::getInstance().canPersonDelete(personID))
    {
        QMessageBox::critical(this,"错误","存在包含该个人的房屋或合同，无法删除。");
        return;
    }

    if (QMessageBox::warning(this,"警告","删除记录后将无法恢复，确定吗？",QMessageBox::Ok,QMessageBox::Cancel|QMessageBox::Default)==QMessageBox::Ok)
    {
        DatabaseManager::getInstance().deletePerson(personID);
        refreshPersonTable();
    }
}

void MainWindow::on_tableViewContract_doubleClicked(const QModelIndex &index)
{
    currentContractIndex=index;
    emit on_editContractButton_clicked();
}

void MainWindow::on_tableViewHouse_doubleClicked(const QModelIndex &index)
{
    currentHouseIndex=index;
    emit on_editHouseButton_clicked();
}

void MainWindow::on_tableViewPerson_doubleClicked(const QModelIndex &index)
{
    currentPersonIndex=index;
    emit on_editPersonButton_clicked();
}
