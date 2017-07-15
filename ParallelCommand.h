#ifndef PARALLELCOMMAND_H
#define PARALLELCOMMAND_H

#include"Command.h"
#include"IRunnable.h"

class ParallelCommand : public Command{
public:
    ParallelCommand(int timeout, string description);
    
    ParallelCommand();

    virtual Result Run(vector<string> params = vector<string>()) override;
};

#endif