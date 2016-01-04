#include "person.h"

bool Person::isIDValid(string id)
{
    int i,sum,n;
    if (id.length()!=18)
        return false;
    for (sum=i=0;i<17;i++)
        sum+=((1<<(18-i-1))%11)*(id[i]-'0');
    n=(12-(sum%11))%11;
    return ((n<10 && n==id[17]-'0') || (n==10 && id[17]=='X'));
}

//Validity of arguments will be checked before constructor
Person::Person(QString ID,QString name,QString Addr,QString Tel): Identifier(ID), Name(name), Address(Addr), TelNumber(Tel),
    Birthday(QDate::fromString(ID.mid(6,8),"yyyyMMdd"))
{
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

QString Person::getTel() const
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










