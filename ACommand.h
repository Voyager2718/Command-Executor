#ifndef ACOMMAND_H
#define ACOMMAND_H

#include<list>
#include<string>
#include"IRunnable.h"
#include"IValidator.h"
#include"IOutputChecker.h"

using std::list;
using std::string;

class ACommand : public IRunnable{
private:
    int timeout;
    list<IValidator> validators;
    list<IOutputChecker> outputCheckers;
    string description;
public:
    ACommand(int timeout, string description);

    ACommand();

    virtual ~ACommand() = default;

    ACommand(const ACommand& command) = default;

    Result Run(vector<string> params = vector<string>()) = 0;

    virtual void SetTimeout(int timeout);

    virtual int GetTimeout();

    virtual void AddValidator(IValidator validator);

    virtual void AddOutputChecker(IOutputChecker outputChecker);

    virtual string GetDescription();
};

#endif