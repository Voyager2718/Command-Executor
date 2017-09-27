#ifndef REPORT_STRING_H
#define REPORT_STRING_H

#include <string>

#include <map>

using std::string;
using std::to_string;

using std::map;

enum ReportType
{
  FATAL,
  WARNING,
  INFO,
  SUCCESS
};

class ReportString
{
private:
  ReportString();

  map<string, string> reportStrings;

public:
  static ReportString &GetInstance();

  /**
    * Return 0 if successful, return non 0 otherwise.
    */
  int AddReportString(ReportType type, string reportno, string description);

  string GetReportString(string reference, string fromFile);
};

#endif