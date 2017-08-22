#ifndef GLOBALAREA_H
#define GLOBALAREA_H

#include <string>

#include <map>

using std::string;

using std::map;

class GlobalArea final
{
  private:
    GlobalArea();

    map<string, string> data;

  public:
    static GlobalArea &GetInstance();

    void AddData(string name, string value);

    string GetData(string name);
};

#endif