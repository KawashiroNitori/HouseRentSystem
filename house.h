#ifndef HOUSE_H
#define HOUSE_H
#include "person.h"
#include <cstdint>
#include <QString>
using namespace std;

class House
{
private:
    static int total;
    int64_t Identifier;
    int64_t contractId;
    Person& Owner;
    QString Address;
    double Square;
    QString Type;
    QString Remark;

public:
    House(int64_t t_conId,Person& t_owner,QString t_Addr,double t_Square,QString t_Type,QString t_Remark);
    int64_t getID() const;
    int64_t getContractID() const;
    Person& getOwner() const;
    QString getAddress() const;
    int getSquare() const;
    QString getType() const;
    QString getRemark() const;
    void setContractID(int64_t Id);
    void setOwner(Person& owner);
    void setAddress(QString addr);
    void setSquare(int sq);
    void setType(QString type);
    void setRemark(QString remark);
    static void setTotal(int tot);
};

#endif // HOUSE_H
