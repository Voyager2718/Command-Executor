#ifndef PARALLELCOMMAND_H
#define PARALLELCOMMAND_H

#include <vector>
#include <string>

#include "../Command.h"
#include "../../IRunnable.h"
#include "../../../Result/Result.h"

using std::vector;
using std::string;

class ParallelCommand : public Command
{
  public:
    ParallelCommand(string command);
    
    ParallelCommand(string command, int timeout, string description);

    ParallelCommand(int timeout, string description);

    ParallelCommand();
};

#endif