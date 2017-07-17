#ifndef COMMAND_H
#define COMMAND_H

#include <list>
#include <string>
#include <unistd.h>
#include <memory>

#include "Report.h"
#include "IRunnable.h"
#include "AValidator.h"
#include "AOutputChecker.h"

using std::list;
using std::string;

using std::shared_ptr;

class Command : public IRunnable
{
  protected:
    int timeout;
    list<shared_ptr<AValidator>> validators;
    list<shared_ptr<AOutputChecker>> outputCheckers;
    string command;
    string description = "Default command.";

  public:
    Command(int timeout, string description);

    Command();

    virtual ~Command() = default;

    Command(const Command &command) = default;

    virtual Result Run(vector<string> params = vector<string>()) override;

    virtual void SetCommand(string command);

    virtual string GetCommand();

    virtual void SetTimeout(int timeout);

    virtual int GetTimeout();

    virtual void AddValidator(shared_ptr<AValidator> validator);

    virtual void AddOutputChecker(shared_ptr<AOutputChecker> outputChecker);

    virtual string GetDescription();
};

#endif