#pragma execution_character_set("utf-8")

#include "databasemanager.h"
#include <fstream>
#include <QMessageBox>

using namespace std;

DatabaseManager* DatabaseManager::instancePtr=NULL;

const QString DatabaseManager::personHeaderData[]={"身份证号","姓名","地址","电话"};
const QString DatabaseManager::houseHeaderData[]={"编号","所有人","地址","面积","户型","备注"};
const QString DatabaseManager::contractHeaderData[]={"编号","租赁人","房屋","开始日期","结束日期","租金","备注"};

DatabaseManager::DatabaseManager() :
    db(QSqlDatabase::addDatabase("QSQLITE"))
{
    ifstream file("database.db");
    if (!file.is_open())
    {
        db.setDatabaseName("database.db");
        db.open();
        QSqlQuery query;
        query.exec("CREATE TABLE person(id VARCHAR PRIMARY KEY,name VARCHAR,address VARCHAR,tel VARCHAR)");
        query.exec("CREATE TABLE house(id VARCHAR PRIMARY KEY,owner VARCHAR,address VARCHAR,square DECIMAL,type VARCHAR,remark VARCHAR)");
        query.exec("CREATE TABLE contract(id VARCHAR PRIMARY KEY,holder VARCHAR,house VARCHAR,start_date DATE,end_date DATE,rent INTEGER,remark VARCHAR)");
    }
    else
    {
        file.close();
        db.setDatabaseName("database.db");
        db.open();
    }

}

DatabaseManager& DatabaseManager::getInstance()
{
    if (!instancePtr)
        instancePtr=new DatabaseManager;
    return *instancePtr;
}

QSqlQueryModel *DatabaseManager::searchPerson(const QString &key, bool isTemp)
{
    QSqlQueryModel* model=NULL;
    if (isTemp)
        model=&tempModel;
    else
        model=&personModel;

    model->setQuery(QString("SELECT * FROM person WHERE id LIKE '%%1%' OR name LIKE '%%1%' OR address LIKE '%%1%' OR tel LIKE '%%1%'").arg(key));
    for (int i=0;i<4;i++)
        model->setHeaderData(i,Qt::Horizontal,personHeaderData[i]);
    return model;
}

QSqlQueryModel* DatabaseManager::allPerson(bool isTemp)
{
    QSqlQueryModel* model=NULL;
    if (isTemp)
        model=&tempModel;
    else
        model=&personModel;

    model->setQuery("SELECT * FROM person");
    for (int i=0;i<4;i++)
        model->setHeaderData(i,Qt::Horizontal,personHeaderData[i]);
    return model;
}

Person DatabaseManager::buildPerson(const QString &id)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM person WHERE id='%1'").arg(id));
    query.next();
    return Person(query.value(0).toString(),
                  query.value(1).toString(),
                  query.value(2).toString(),
                  query.value(3).toString());
}

QSqlQueryModel* DatabaseManager::searchHouse(const QString& key, bool isTemp)
{
    QSqlQueryModel* model=NULL;
    if (isTemp)
        model=&tempModel;
    else
        model=&houseModel;

    model->setQuery(QString("SELECT * FROM house WHERE id LIKE '%%1%' OR owner LIKE '%%1%' OR address LIKE '%%1%' OR type LIKE '%%1%'").arg(key));
    for (int i=0;i<6;i++)
        model->setHeaderData(i,Qt::Horizontal,houseHeaderData[i]);
    return model;
}

QSqlQueryModel* DatabaseManager::allHouse(bool isTemp)
{
    QSqlQueryModel* model=NULL;
    if (isTemp)
        model=&tempModel;
    else
        model=&houseModel;

    model->setQuery("SELECT * FROM house");
    for (int i=0;i<6;i++)
        model->setHeaderData(i,Qt::Horizontal,houseHeaderData[i]);
    return model;
}

House DatabaseManager::buildHouse(const QString &id)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM house WHERE id='%1'").arg(id));
    query.next();
    return House(query.value(0).toString(),
                 buildPerson(query.value(1).toString()),
                 query.value(2).toString(),
                 query.value(3).toDouble(),
                 query.value(4).toString(),
                 query.value(5).toString());
}

QSqlQueryModel* DatabaseManager::searchContract(const QString &key, bool isTemp)
{
    QSqlQueryModel* model=NULL;
    if (isTemp)
        model=&tempModel;
    else
        model=&contractModel;

    model->setQuery(QString("SELECT * FROM contract WHERE id LIKE '%%1%' OR holder LIKE '%%1%' OR house LIKE '%%1%'").arg(key));
    for (int i=0;i<7;i++)
        model->setHeaderData(i,Qt::Horizontal,contractHeaderData[i]);
    return model;
}

QSqlQueryModel* DatabaseManager::allContract(bool isTemp)
{
    QSqlQueryModel* model=NULL;
    if (isTemp)
        model=&tempModel;
    else
        model=&contractModel;

    model->setQuery("SELECT * FROM contract");
    for (int i=0;i<7;i++)
        model->setHeaderData(i,Qt::Horizontal,contractHeaderData[i]);
    return model;
}

Contract DatabaseManager::buildContract(const QString &id)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM contract WHERE id='%1'").arg(id));
    query.next();
    return Contract(query.value(0).toString(),
                    buildPerson(query.value(1).toString()),
                    buildHouse(query.value(2).toString()),
                    query.value(3).toDate(),
                    query.value(4).toDate(),
                    query.value(5).toInt(),
                    query.value(6).toString());
}

void DatabaseManager::insertPerson(const Person &p)
{
    QSqlQuery query;
    query.exec(QString("INSERT INTO person VALUES ('%1', '%2', '%3', '%4')").arg(p.getID(),p.getName(),p.getAddress(),p.getTel()));
}

void DatabaseManager::updatePerson(const Person &p)
{
    QSqlQuery query;
    query.exec(QString("UPDATE person SET name='%2', address='%3', tel='%4' WHERE id='%1'").arg(p.getID(),p.getName(),p.getAddress(),p.getTel()));
}

void DatabaseManager::deletePerson(const QString &id)
{
    QSqlQuery query;
    query.exec(QString("DELETE FROM person WHERE id='%1'").arg(id));
}

void DatabaseManager::insertHouse(const House &h)
{
    QSqlQuery query;
    query.exec(QString("INSERT INTO house VALUES ('%1','%2','%3',%4,'%5','%6')").arg(h.getID(),
                                                                                     h.getOwner().getID(),
                                                                                     h.getAddress(),
                                                                                     QString::number(h.getSquare()),
                                                                                     h.getType(),
                                                                                     h.getRemark()));
}

void DatabaseManager::updateHouse(const House &h)
{
    QSqlQuery query;
    query.exec(QString("UPDATE house SET owner='%2', address='%3', square=%4, type='%5', remark='%6' WHERE id='%1'").arg(h.getID(),
                                                                                                                         h.getOwner().getID(),
                                                                                                                         h.getAddress(),
                                                                                                                         QString::number(h.getSquare()),
                                                                                                                         h.getType(),
                                                                                                                         h.getRemark()));
}

void DatabaseManager::deleteHouse(const QString &id)
{
    QSqlQuery query;
    query.exec(QString("DELETE FROM house WHERE id='%1'").arg(id));
}

void DatabaseManager::insertContract(const Contract &c)
{
    QSqlQuery query;
    query.exec(QString("INSERT INTO contract VALUES ('%1','%2','%3','%4','%5',%6,'%7')").arg(c.getID(),
                                                                                             c.getHolder().getID(),
                                                                                             c.getHouse().getID(),
                                                                                             c.getStartDate().toString(Qt::ISODate),
                                                                                             c.getEndDate().toString(Qt::ISODate),
                                                                                             QString::number(c.getRent()),
                                                                                             c.getRemark()));
}

void DatabaseManager::updateContract(const Contract &c)
{
    QSqlQuery query;
    query.exec(QString("UPDATE contract SET holder='%2', house='%3', start_date='%4', end_date='%5', rent=%6, remark='%7' WHERE id='%1'").arg(c.getID(),
                                                                                                                                              c.getHolder().getID(),
                                                                                                                                              c.getHouse().getID(),
                                                                                                                                              c.getStartDate().toString(Qt::ISODate),
                                                                                                                                              c.getEndDate().toString(Qt::ISODate),
                                                                                                                                              QString::number(c.getRent()),
                                                                                                                                              c.getRemark()));
}

void DatabaseManager::deleteContract(const QString &id)
{
    QSqlQuery query;
    query.exec(QString("DELETE FROM contract WHERE id='%1'").arg(id));
}

bool DatabaseManager::isPersonIDExisted(const QString &id)
{
    QSqlQuery query;
    query.exec(QString("SELECT id FROM person WHERE id='%1' LIMIT 1").arg(id));
    return query.next();
}

bool DatabaseManager::isHouseIDExisted(const QString &id)
{
    QSqlQuery query;
    query.exec(QString("SELECT id FROM house WHERE id='%1' LIMIT 1").arg(id));
    return query.next();
}

bool DatabaseManager::isContractIDExisted(const QString &id)
{
    QSqlQuery query;
    query.exec(QString("SELECT id FROM contract WHERE id='%1' LIMIT 1").arg(id));
    return query.next();
}

bool DatabaseManager::canPersonDelete(const QString &id)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM house WHERE owner='%1'").arg(id));
    if (query.next())
        return false;
    query.exec(QString("SELECT * FROM contract WHERE holder='%1'").arg(id));
    if (query.next())
        return false;

    return true;
}

bool DatabaseManager::canHouseDelete(const QString &id)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM contract WHERE house='%1'").arg(id));
    return !query.next();
}

QString DatabaseManager::getNewHouseID()
{
    QString nowDateStr=QDate::currentDate().toString("yyyyMMdd");
    int number=1;
    QSqlQuery query;
    if (!query.exec(QString("SELECT SUBSTR(id,10) FROM house WHERE id LIKE 'H%1%' ORDER BY id DESC").arg(nowDateStr)))
        QMessageBox::critical(NULL,"error",db.lastError().text());
    if (query.next())
        number=query.value(0).toString().toInt()+1;
    if (number>9999)
    {
        return "";
    }
    QString numberStr=QString::number(number).sprintf("%04d",number);
    return QString("H%1%2").arg(nowDateStr,numberStr);
}

QString DatabaseManager::getNewContractID()
{
    QString nowDateStr=QDate::currentDate().toString("yyyyMMdd");
    int number=1;
    QSqlQuery query;
    query.exec(QString("SELECT SUBSTR(id,10) FROM contract WHERE id LIKE 'C%1%' ORDER BY id DESC").arg(nowDateStr));
    if (query.next())
        number=query.value(0).toString().toInt()+1;
    if (number>9999)
    {
        return "";
    }
    QString numberStr=QString::number(number).sprintf("%04d",number);
    return QString("C%1%2").arg(nowDateStr,numberStr);
}
