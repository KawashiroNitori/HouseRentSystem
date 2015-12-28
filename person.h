#ifndef PERSON_H
#define PERSON_H
#include <cstdint>
#include <QDate>
#include <QString>
using namespace std;

#define SEXTYPE int8_t
#define SEX_MALE 1
#define SEX_FEMALE 0

class Person
{
private:
    QString Identifier;
    QString Name;
    SEXTYPE Sex;
    QString Address;
    int Age;
    QDate Birthday;
    int64_t TelNumber;

public:
    static bool isIDValid(string id);
    Person(QString ID,QString name,QString Addr,int64_t Tel);
    QString getID() const;
    QString getName() const;
    SEXTYPE getSex() const;
    QString getAddress() const;
    int getAge() const;
    QDate getBirthday() const;
    int64_t getTel() const;
    void setName(QString name);
    void setAddress(QString Addr);
    void setTel(int64_t tel);
};

#endif // PERSON_H
