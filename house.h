#ifndef HOUSE_H
#define HOUSE_H
#include "person.h"
#include <cstdint>
#include <QString>
using namespace std;

class House
{
private:
    QString Identifier;
    QString contractId;
    Person& Owner;
    QString Address;
    double Square;
    QString Type;
    QString Remark;

public:
    House(QString t_conId, Person& t_owner, QString t_Addr, double t_Square, QString t_Type, QString t_Remark);
    QString getID() const;
    const QString getContractID() const;
    Person& getOwner() const;
    QString getAddress() const;
    double getSquare() const;
    QString getType() const;
    QString getRemark() const;
    void setContractID(int64_t Id);
    void setOwner(Person& owner);
    void setAddress(QString addr);
    void setSquare(double sq);
    void setType(QString type);
    void setRemark(QString remark);
};

#endif // HOUSE_H
