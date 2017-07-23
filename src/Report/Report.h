#ifndef REPORT_H
#define REPORT_H

#include <list>
#include <map>
#include <string>
#include <iostream>
#include <functional>

#include "../../lib/ytime/ytime.h"
#include "../Result/Result.h"

using std::list;
using std::map;
using std::function;
using std::string;
using std::cout;
using std::endl;

class Report final
{
private:
  Report() {}

  list<map<string, string>> a; // map{timestamp, user defined report string}

  list<map<string, string>> reports;

  static void Printer(string timestamp, string result, string report);

public:
  static Report &GetInstance();

  Report(const Report &) = delete;

  void AddReport(string report, Result result = SUCCESSFUL);

  list<map<string, string>> GetReports();

  void PrintReport(function<void(string, string, string)> = Printer);

  void PrintSuccessfulReport(function<void(string, string, string)> = Printer);

  void PrintFailedReport(function<void(string, string, string)> = Printer);
};

#endif