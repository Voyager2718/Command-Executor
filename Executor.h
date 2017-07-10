#ifndef EXECUTOR_H
#define EXECUTOR_H

#include<list>
#include"Result.h"
#include"IRunnable.h"

using std::list;

class Executor{
private:
    list<IRunnable> runnables;

public:
    Executor(IRunnable runnable);    

    virtual ~Executor() = default;

    Executor(const Executor& executor) = default;

    virtual void AddRunnable(IRunnable runnable);

    virtual Result Execute();
};

#endif