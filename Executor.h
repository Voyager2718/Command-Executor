#ifndef EXECUTOR_H
#define EXECUTOR_H

#include<list>
#include"ACommand.h"

using std::list;

class Executor{
private:
    list<ACommand> commands;

public:
    Executor(ACommand command);

    virtual ~Executor() = default;

    Executor(const Executor& executor) = default;

    Result Execute();
};

#endif