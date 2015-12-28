#include "house.h"
#include "configmanager.h"

House::House(QString t_conId,Person& t_owner,QString t_Addr,double t_Square,QString t_Type,QString t_Remark):
    contractId(t_conId),
    Owner(t_owner),
    Address(t_Addr),
    Square(t_Square),
    Type(t_Type),
    Remark(t_Remark)
{
    Identifier="H";
    Identifier+=QDate::currentDate().toString("yyyyMMdd");
    Identifier+=QString("%1").arg(ConfigManager::getInstance().addTotal(),4,10,QChar('0'));

}

QString House::getID() const
{
    return Identifier;
}

const QString House::getContractID() const
{
    return contractId;
}

Person& House::getOwner() const
{
    return Owner;
}

QString House::getAddress() const
{
    return Address;
}

double House::getSquare() const
{
    return Square;
}

QString House::getType() const
{
    return Type;
}

QString House::getRemark() const
{
    return Remark;
}

void House::setContractID(int64_t Id)
{
    contractId=Id;
    //need to check the ID is exist, NOT finished
}

void House::setOwner(Person &owner)
{
    Owner=owner;
    //need to check the ID is exist, NOT finished
}

void House::setAddress(QString addr)
{
    Address=addr;
}

void House::setSquare(double sq)
{
    Square=sq;
}

void House::setType(QString type)
{
    Type=type;
}

void House::setRemark(QString remark)
{
    Remark=remark;
}











