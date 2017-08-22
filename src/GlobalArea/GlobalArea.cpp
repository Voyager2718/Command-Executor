#include "GlobalArea.h"

GlobalArea &GlobalArea::GetInstance()
{
    static GlobalArea instance;
    return instance;
}

void GlobalArea::AddData(string name, string value)
{
    data.insert({name, value});
}

string GlobalArea::GetData(string name)
{
    return data[name];
}