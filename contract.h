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
    House house;
    Person Holder;
    int32_t rent;
    QDate startDate;
    QDate endDate;
    QString Remark;

public:
    Contract(QString id,Person& t_Holder,House& t_house,QDate t_startDate,QDate t_endDate,int32_t t_rent,QString t_Remark);
    QString getID() const;
    House getHouse() const;
    Person getOwner() const;
    Person getHolder() const;
    int32_t getRent() const;
    QDate getStartDate() const;
    QDate getEndDate() const;
    QString getRemark() const;
    void setRent(int32_t _rent);
    void setStartDate(QDate date);
    void setStartDate(int year,int month,int day);
    bool setEndDate(QDate date);
    bool setEndDate(int year,int month,int day);
    void setRemark(QString remark);

};

#endif // CONTRACT_H
