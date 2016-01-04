#include "contract.h"

Contract::Contract(QString id, Person &t_Holder, House &t_house, QDate t_startDate, QDate t_endDate, int32_t t_rent, QString t_Remark):
    Identifier(id),
    house(t_house),
    Holder(t_Holder),
    startDate(t_startDate),
    endDate(t_endDate),
    rent(t_rent),
    Remark(t_Remark)
{
}

QString Contract::getID() const
{
    return Identifier;
}

House Contract::getHouse() const
{
    return house;
}

Person Contract::getOwner() const
{
    return house.getOwner();
}

Person Contract::getHolder() const
{
    return Holder;
}

int32_t Contract::getRent() const
{
    return rent;
}

QDate Contract::getStartDate() const
{
    return startDate;
}

QDate Contract::getEndDate() const
{
    return endDate;
}

QString Contract::getRemark() const
{
    return Remark;
}

void Contract::setRent(int32_t _rent)
{
    rent=_rent;
}

void Contract::setStartDate(QDate date)
{
    startDate=date;
}

void Contract::setStartDate(int year, int month, int day)
{
    startDate.setDate(year,month,day);
}

bool Contract::setEndDate(QDate date)
{
    if (date<QDate::currentDate())
    {
        endDate=date;
        return true;
    }
    else
        return false;
}

bool Contract::setEndDate(int year, int month, int day)
{
    QDate tempDate(year,month,day);
    if (tempDate<QDate::currentDate())
    {
        endDate=tempDate;
        return true;
    }
    else
        return false;
}

void Contract::setRemark(QString remark)
{
    Remark=remark;
}












