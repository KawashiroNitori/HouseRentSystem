#include "dialogselecthouse.h"
#include "ui_dialogselecthouse.h"

DialogSelectHouse::DialogSelectHouse(House **h, QWidget *parent) :
    house(h),
    QDialog(parent),
    ui(new Ui::DialogSelectHouse)
{
    ui->setupUi(this);
    setWindowTitle("选择房屋");
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

DialogSelectHouse::~DialogSelectHouse()
{
    delete ui;
}

void DialogSelectHouse::on_searchButton_clicked()
{
    model=DatabaseManager::getInstance().searchHouse(ui->lineEdit->text());
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(5);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void DialogSelectHouse::on_lineEdit_textChanged(const QString &str)
{
    ui->searchButton->setEnabled(str.length()>0);
}

void DialogSelectHouse::on_tableView_clicked(const QModelIndex &index)
{
    currentIndex=index;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}


void DialogSelectHouse::on_buttonBox_accepted()
{
    QString t_id=model->record(currentIndex.row()).value("id").toString();
    Person t_owner=DatabaseManager::getInstance().buildPerson(model->record(currentIndex.row()).value("owner").toString());
    QString t_addr=model->record(currentIndex.row()).value("address").toString();
    double t_square=model->record(currentIndex.row()).value("square").toDouble();
    QString t_type=model->record(currentIndex.row()).value("type").toString();
    QString t_remark=model->record(currentIndex.row()).value("remark").toString();
    if (house && !*house)
        *house=new House(t_id,t_owner,t_addr,t_square,t_type,t_remark);
    else
        **house=House(t_id,t_owner,t_addr,t_square,t_type,t_remark);
}

void DialogSelectHouse::on_seeAllButton_clicked()
{
    model=DatabaseManager::getInstance().allHouse();
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(5);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void DialogSelectHouse::on_tableView_doubleClicked(const QModelIndex &index)
{
    currentIndex=index;
    on_buttonBox_accepted();
    this->accept();
}
