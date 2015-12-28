#include "configmanager.h"
#include "json/json.h"

ConfigManager* ConfigManager::instancePtr=NULL;

ConfigManager::ConfigManager()
{
    root["LastDate"]=QDate::currentDate().toString(Qt::ISODate).toStdString();
    root["TotalNumber"]=0;

    Json::Reader reader;
    ifstream file("Config.json");
    if (!file.is_open() || !reader.parse(file,root,false))
    {
        if (file.is_open())
            file.close();
        WriteJSONFile();
        return;
    }

    if (QDate::fromString(QString(root["LastDate"].asString().c_str()),Qt::ISODate)!=QDate::currentDate())
    {
        root["LastDate"]=QDate::currentDate().toString(Qt::ISODate).toStdString();
        root["TotalNumber"]=0;
        WriteJSONFile();
    }

}

ConfigManager& ConfigManager::getInstance()
{
    if (!instancePtr)
        instancePtr=new ConfigManager();
    return *instancePtr;
}

void ConfigManager::WriteJSONFile()
{
    ofstream file("Config.json");
    if (!file.is_open())
        return;
    file<<root;
    file.close();
}

int32_t ConfigManager::getTotal() const
{
    return root["TotalNumber"].asInt();
}

int32_t ConfigManager::addTotal()
{
    int32_t n=root["TotalNumber"].asInt();
    root["TotalNumber"]=n+1;
    WriteJSONFile();
    return root["TotalNumber"].asInt();
}
