#ifndef AVALIDATOR_H
#define AVALIDATOR_H

#include<map>
#include<string>
#include"Result.h"

using std::map;
using std::string;

class AValidator{
private:
    map<string, string> values;
    string description;
    string exceptionDescription;
    string successDescription;
public:
    AValidator() = default;

    virtual ~AValidator() = default;

    virtual AValidator(const IValidator& validator) = default;

    virtual Result Verify() = 0;

    virtual string getSuccessDescription();

    virtual string getExceptionDescription();

    virtual map<string, string> getValuesMap();
};

#endif