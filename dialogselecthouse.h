#ifndef DIALOGSELECTHOUSE_H
#define DIALOGSELECTHOUSE_H

#include <QDialog>
#include <QtSql/QtSql>
#include "house.h"
#include "databasemanager.h"

namespace Ui {
class DialogSelectHouse;
}

class DialogSelectHouse : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSelectHouse(House** h,QWidget *parent = 0);
    ~DialogSelectHouse();

private slots:
    void on_searchButton_clicked();

    void on_lineEdit_textChanged(const QString &str);

    void on_tableView_clicked(const QModelIndex &index);

    void on_buttonBox_accepted();

    void on_seeAllButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::DialogSelectHouse *ui;
    QSqlQueryModel* model;
    House** house;
    QModelIndex currentIndex;
};

#endif // DIALOGSELECTHOUSE_H
