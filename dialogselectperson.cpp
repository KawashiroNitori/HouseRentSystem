#include "dialogselectperson.h"
#include "ui_dialogselectperson.h"
#include "databasemanager.h"

DialogSelectPerson::DialogSelectPerson(Person **_person, QWidget *parent) :
    QDialog(parent),
    person(_person),
    ui(new Ui::DialogSelectPerson)
{
    ui->setupUi(this);
    setWindowTitle("选择个人");
    setWindowFlags(Qt::Dialog|Qt::WindowCloseButtonHint);
    setFixedSize(size());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->searchButton->setEnabled(false);
    ui->searchButton->setDefault(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(QString("确定"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(QString("取消"));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

DialogSelectPerson::~DialogSelectPerson()
{
    delete ui;
}


void DialogSelectPerson::on_searchButton_clicked()
{
    model=DatabaseManager::getInstance().searchPerson(ui->lineEdit->text());
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}


void DialogSelectPerson::on_lineEdit_textEdited(const QString &str)
{
    ui->searchButton->setEnabled(str.length()>0);
}

void DialogSelectPerson::on_tableView_clicked(const QModelIndex &index)
{
    currentIndex=index;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void DialogSelectPerson::on_buttonBox_accepted()
{
    QString t_id=model->record(currentIndex.row()).value("id").toString();
    QString t_name=model->record(currentIndex.row()).value("name").toString();
    QString t_addr=model->record(currentIndex.row()).value("address").toString();
    QString t_tel=model->record(currentIndex.row()).value("tel").toString();
    if (person && !*person)
        *person=new Person(t_id,t_name,t_addr,t_tel);
    else
        **person=Person(t_id,t_name,t_addr,t_tel);
}

void DialogSelectPerson::on_seeAllButton_clicked()
{
    model=DatabaseManager::getInstance().allPerson();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void DialogSelectPerson::on_tableView_doubleClicked(const QModelIndex &index)
{
    currentIndex=index;
    on_buttonBox_accepted();
    this->accept();
}
