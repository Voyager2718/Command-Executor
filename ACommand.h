#ifndef ACOMMAND_H
#define ACOMMAND_H

#include<list>
#include<string>
#include"IValidator.h"
#include"IOutputChecker.h"

using std::list;
using std::string;

class ACommand{
private:
    int timeOut;
    list<IValidator> validators;
    list<IOutputChecker> outputCheckers;
    string description;
public:
    ACommand(int timeOut, string description);

    virtual ~ACommand() = default;

    ACommand(const ACommand& command) = default;

    Result Run() = 0;

    virtual void SetTimeout(int timeOut);

    virtual void AddValidator(IValidator validator);

    virtual void AddOutputChecker(IOutputChecker outputChecker);

    string GetDescription();
};

#endif