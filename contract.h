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
    static int total;
    int64_t Identifier;
    House& house;
    Person& Holder;
    QDate startDate;
    QDate endDate;
    QString Remark;

public:
    Contract(House& t_house,Person& t_Holder,QDate t_startDate,QDate t_endDate,QString t_Remark);
    House& getHouse() const;
    Person& getOwner() const;
    Person& getHolder() const;
    QDate getStartDate() const;
    QDate getEndDate() const;
    QString getRemark() const;
    void setStartDate(int year,int month,int day);
    bool setEndDate(int year,int month,int day);
    void setRemark(QString remark);
    static void setTotal(int tot);
};

#endif // CONTRACT_H
