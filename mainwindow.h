#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "databasemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void tryEnableSearchButton();

    void on_searchContractButton_clicked();

    void on_allContractButton_clicked();

    void on_searchHouseButton_clicked();

    void on_allHouseButton_clicked();

    void on_searchPersonButton_clicked();

    void on_allPersonButton_clicked();

    void on_tableViewContract_clicked(const QModelIndex &index);

    void on_tableViewHouse_clicked(const QModelIndex &index);

    void on_tableViewPerson_clicked(const QModelIndex &index);

    void on_addContractButton_clicked();

    void on_addHouseButton_clicked();

    void on_addPersonButton_clicked();

    void on_editContractButton_clicked();

    void on_editHouseButton_clicked();

    void on_editPersonButton_clicked();

    void on_deleteContractButton_clicked();

    void on_deleteHouseButton_clicked();

    void on_deletePersonButton_clicked();

    void on_tableViewContract_doubleClicked(const QModelIndex &index);

    void on_tableViewHouse_doubleClicked(const QModelIndex &index);

    void on_tableViewPerson_doubleClicked(const QModelIndex &index);

private:
    QString lastContractStr;
    QString lastHouseStr;
    QString lastPersonStr;
    QModelIndex currentContractIndex;
    QModelIndex currentHouseIndex;
    QModelIndex currentPersonIndex;
    QSqlQueryModel* contractModel;
    QSqlQueryModel* houseModel;
    QSqlQueryModel* personModel;
    Ui::MainWindow *ui;
    void refreshContractTable();
    void refreshHouseTable();
    void refreshPersonTable();

};

#endif // MAINWINDOW_H
