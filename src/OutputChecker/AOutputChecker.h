#ifndef AOUTPUTCHECKER_H
#define AOUTPUTCHECKER_H

#include <map>
#include <string>
#include "../Result/Result.h"

using std::map;
using std::string;

class AOutputChecker
{
protected:
  map<string, string> values;

public:
  AOutputChecker() = default;

  virtual ~AOutputChecker() = default;

  AOutputChecker(const AOutputChecker &outputChecker) = default;

  virtual Result Check(string allOutput) = 0;

  virtual string GetSuccessDescription() = 0;

  virtual string GetFatalDescription() = 0;

  virtual string GetIgnoredDescription() = 0;

  virtual string GetLastReportNumber() = 0;

  virtual map<string, string> GetValuesMap();
};

#endif