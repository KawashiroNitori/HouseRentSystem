#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QtSql>
#include "person.h"
#include "house.h"
#include "contract.h"
//using namespace Qt;

class DatabaseManager
{
public:
    static DatabaseManager& getInstance();
    bool isPersonIDExisted(const QString& id);
    bool isHouseIDExisted(const QString& id);
    bool isContractIDExisted(const QString& id);
    bool canPersonDelete(const QString& id);
    bool canHouseDelete(const QString& id);
    QSqlQueryModel* searchPerson(const QString& key,bool isTemp=true);
    QSqlQueryModel* allPerson(bool isTemp=true);
    Person buildPerson(const QString& id);
    QSqlQueryModel* searchHouse(const QString& key,bool isTemp=true);
    QSqlQueryModel* allHouse(bool isTemp=true);
    House buildHouse(const QString& id);
    QSqlQueryModel* searchContract(const QString& key,bool isTemp=true);
    QSqlQueryModel* allContract(bool isTemp=true);
    Contract buildContract(const QString& id);
    void insertPerson(const Person& p);
    void updatePerson(const Person& p);
    void deletePerson(const QString& id);
    void insertHouse(const House& h);
    void updateHouse(const House& h);
    void deleteHouse(const QString& id);
    void insertContract(const Contract& c);
    void updateContract(const Contract& c);
    void deleteContract(const QString& id);
    QString getNewHouseID();
    QString getNewContractID();

private:
    const static QString personHeaderData[];
    const static QString houseHeaderData[];
    const static QString contractHeaderData[];
    DatabaseManager();
    static DatabaseManager* instancePtr;
    QSqlDatabase db;
    QSqlQueryModel tempModel;
    QSqlQueryModel personModel;
    QSqlQueryModel houseModel;
    QSqlQueryModel contractModel;

};

#endif // DATABASEMANAGER_H
