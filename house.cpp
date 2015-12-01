#include "house.h"

int House::total=10000;

House::House(int64_t t_conId,Person& t_owner,QString t_Addr,int t_Square,QString t_Type,QString t_Remark):
    contractId(t_conId),
    Owner(t_owner),
    Address(t_Addr),
    Square(t_Square),
    Type(t_Type),
    Remark(t_Remark)
{
    Identifier=++total;
}

int64_t House::getID() const
{
    return Identifier;
}

int64_t House::getContractID() const
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

int House::getSquare() const
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

void House::setSquare(int sq)
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

void House::setTotal(int tot)
{
    total=tot;
    //temp
}












