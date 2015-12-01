#include "person.h"

//Validity of arguments will be checked before constructor
Person::Person(QString ID,QString name,QString Addr,int64_t Tel): Identifier(ID), Name(name), Address(Addr), TelNumber(Tel)
{
    int year=0,month=0,day=0;
    for (int i=6;i<=9;i++)
    {
        year*=10;
        year+=ID[i].digitValue();
    }
    for (int i=10;i<=11;i++)
    {
        month*=10;
        month+=ID[i].digitValue();
    }
    for (int i=12;i<=13;i++)
    {
        day*=10;
        day+=ID[i].digitValue();
    }
    Birthday.setDate(year,month,day);
    Sex=ID[16].digitValue()&1;

    QDate nowDate=QDate::currentDate();
    Age=nowDate.year()-Birthday.year();
    if (nowDate.month()<Birthday.month())
        --Age;
    else if (nowDate.month()==Birthday.month() && nowDate.day()<Birthday.day())
        --Age;

}


QString Person::getID() const
{
    return Identifier;
}

QString Person::getName() const
{
    return Name;
}

SEXTYPE Person::getSex() const
{
    return Sex;
}

QString Person::getAddress() const
{
    return Address;
}

int Person::getAge() const
{
    return Age;
}

QDate Person::getBirthday() const
{
    return Birthday;
}

int64_t Person::getTel() const
{
    return TelNumber;
}

void Person::setName(QString name)
{
    Name=name;
}

void Person::setAddress(QString Addr)
{
    Address=Addr;
}

void Person::setTel(int64_t tel)
{
    TelNumber=tel;
}










