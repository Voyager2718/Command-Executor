#ifndef EXECUTOR_H
#define EXECUTOR_H

#include<list>
#include<functional>
#include"Result.h"
#include"IRunnable.h"
#include"Report.h"

using std::list;
using std::function;

class Executor{
protected:
    list<IRunnable> runnables;

    virtual void success(){
        Report::GetInstance().PrintReport();
    }

    virtual void fail(){
        Report::GetInstance().PrintReport();
    }

public:
    Executor(IRunnable runnable);    

    virtual ~Executor() = default;

    Executor(const Executor& executor) = default;

    virtual void AddRunnable(IRunnable runnable);

    virtual Result Execute(function<void()>success, function<void()>fail);
};

#endif