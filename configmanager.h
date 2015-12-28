#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#pragma comment(lib,"libjson.lib")
#include "json/json.h"
#include <fstream>
#include <cstdint>
#include <QDate>
using namespace std;

class ConfigManager
{
private:
    static ConfigManager* instancePtr;
    ConfigManager();
    void WriteJSONFile();
    Json::Value root;

public:
    static ConfigManager& getInstance();
    int32_t getTotal() const;
    int32_t addTotal();

};

#endif // CONFIGMANAGER_H
