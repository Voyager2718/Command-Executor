#ifndef REPORT_H
#define REPORT_H

#include <list>
#include <map>
#include <string>
#include <iostream>
#include <functional>
#include <thread>
#include <mutex>

#include "../../lib/ytime/ytime.h"
#include "../Result/Result.h"

using std::list;
using std::map;
using std::mutex;
using std::function;
using std::string;
using std::cout;
using std::endl;

class Report final
{
private:
  Report() {}

  list<map<string, string>> reports; // map{timestamp, user defined report string}

  static void Printer(string timestamp, string result, string report);

  mutex m;

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