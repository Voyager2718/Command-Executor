#ifndef AOUTPUTCHECKER_H
#define AOUTPUTCHECKER_H

#include<map>
#include<string>
#include"Result.h"

using std::map;
using std::string;

class AOutputChecker{
private:
    map<string, string> values;
    string description;
    string exceptionDescription;
    string successDescription;
public:
    AOutputChecker() = default;

    virtual ~AOutputChecker() = default;

    virtual AOutputChecker(const AOutputChecker& outputChecker) = default;

    virtual Result Check(); // FIXME: Put output into check or use another mechanism?

    virtual string getSuccessDescription();

    virtual string getExceptionDescription();

    virtual map<string, string> getValuesMap();
};

#endif