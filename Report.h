#ifndef REPORT_H
#define REPORT_H

#include<list>
#include<map>
#include<string>

#include"lib/ytime.h"

using std::list;
using std::map;
using std::string;

class Report final{
private:
    Report(){}

    list< map<string, string> > reports;    // map<timestamp, user defined report string>
public:
    static Report& GetInstance();

    void AddReport(string report);

    list< map<string, string> > GetReports();
};

#endif