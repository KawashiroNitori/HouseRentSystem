#include "contract.h"
#include "configmanager.h"

Contract::Contract(House& t_house,Person& t_Holder,QDate t_startDate,QDate t_endDate,QString t_Remark):
    house(t_house),
    Holder(t_Holder),
    startDate(t_startDate),
    endDate(t_endDate),
    Remark(t_Remark)
{
    Identifier="C";
    Identifier+=QDate::currentDate().toString("yyyyMMdd");
    Identifier+=QString("%1").arg(ConfigManager::getInstance().addTotal(),4,10,QChar('0'));

}

const QString Contract::getID() const
{
    return Identifier;
}

House& Contract::getHouse() const
{
    return house;
}

Person& Contract::getOwner() const
{
    return house.getOwner();
}

Person& Contract::getHolder() const
{
    return Holder;
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

void Contract::setRent(uint32_t _rent)
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












