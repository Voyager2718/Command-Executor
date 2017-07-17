#ifndef PARALLELCOMMAND_H
#define PARALLELCOMMAND_H

#include<vector>
#include<string>

#include"Command.h"
#include"IRunnable.h"
#include"Result.h"

using std::vector;
using std::string;

class ParallelCommand : public Command{
public:
    ParallelCommand(int timeout, string description);
    
    ParallelCommand();
};

#endif