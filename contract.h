#ifndef CONTRACT_H
#define CONTRACT_H
#include "house.h"
#include "person.h"
#include <cstdint>
#include <QString>
#include <QDate>
using namespace std;

class Contract
{
private:
    QString Identifier;
    House& house;
    Person& Holder;
    uint32_t rent;
    QDate startDate;
    QDate endDate;
    QString Remark;

public:
    Contract(House& t_house,Person& t_Holder,QDate t_startDate,QDate t_endDate,QString t_Remark);
    const QString getID() const;
    House& getHouse() const;
    Person& getOwner() const;
    Person& getHolder() const;
    int32_t getRent() const;
    QDate getStartDate() const;
    QDate getEndDate() const;
    QString getRemark() const;
    void setRent(uint32_t _rent);
    void setStartDate(QDate date);
    void setStartDate(int year,int month,int day);
    bool setEndDate(QDate date);
    bool setEndDate(int year,int month,int day);
    void setRemark(QString remark);

};

#endif // CONTRACT_H
