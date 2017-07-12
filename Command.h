#ifndef COMMAND_H
#define COMMAND_H

#include<list>
#include<string>
#include"IRunnable.h"
#include"IValidator.h"
#include"IOutputChecker.h"

using std::list;
using std::string;

class Command : public IRunnable{
protected:
    int timeout;
    list<IValidator> validators;
    list<IOutputChecker> outputCheckers;
    string description;
public:
    Command(int timeout, string description);

    Command();

    virtual ~Command() = default;

    Command(const Command& command) = default;

    virtual Result Run(vector<string> params = vector<string>());

    virtual void SetTimeout(int timeout);

    virtual int GetTimeout();

    virtual void AddValidator(IValidator validator);

    virtual void AddOutputChecker(IOutputChecker outputChecker);

    virtual string GetDescription();
};

#endif