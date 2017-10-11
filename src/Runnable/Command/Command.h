#ifndef COMMAND_H
#define COMMAND_H

#include <list>
#include <string>
#include <unistd.h>
#include <memory>

#include "../../ReportString/ReportString.h"
#include "../../Report/Report.h"
#include "../IRunnable.h"
#include "../../Validator/AValidator.h"
#include "../../OutputChecker/AOutputChecker.h"
#include "../../OutputChecker/IStdoutChecker.h"
#include "../../OutputChecker/IStderrChecker.h"

using std::list;
using std::string;

using std::shared_ptr;

class Command : public IRunnable
{
protected:
  int timeout;
  list<shared_ptr<AValidator>> validators;
  list<shared_ptr<IStdoutChecker>> stdoutCheckers;
  list<shared_ptr<IStderrChecker>> stderrCheckers;
  string command = "";
  string description = "Default command.";

public:
  Command(string command);

  Command(string command, int timeout, string description);

  Command(int timeout, string description);

  Command();

  virtual ~Command() = default;

  Command(const Command &command) = default;

  virtual Result Run(vector<string> arguments = vector<string>(), bool printOutputs = false) override;

  virtual void SetCommand(string command);

  virtual string GetCommand();

  virtual void SetTimeout(int timeout);

  virtual int GetTimeout();

  virtual void AddValidator(shared_ptr<AValidator> validator);

  virtual void AddStdoutChecker(shared_ptr<IStdoutChecker> stdoutChecker);

  virtual void AddStderrChecker(shared_ptr<IStderrChecker> stderrChecker);

  virtual string GetDescription();
};

#endif