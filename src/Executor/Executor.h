#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <list>
#include <vector>
#include <functional>
#include <memory>

#include "Result.h"
#include "IRunnable.h"
#include "Report.h"

using std::list;
using std::vector;
using std::function;

using std::shared_ptr;

class Executor
{
  private:
    static void success();

    static void fail();

  protected:
    list<shared_ptr<IRunnable>> runnables;

  public:
    Executor(shared_ptr<IRunnable> runnable);

    Executor();

    virtual ~Executor() = default;

    Executor(const Executor &executor) = default;

    virtual void AddRunnable(shared_ptr<IRunnable> runnable);

    virtual Result Execute();

    virtual Result Execute(function<void()> succ, function<void()> fl, vector<string> arguments = vector<string>());

    virtual Result Execute(vector<string> arguments, function<void()> succ = success, function<void()> fl = fail);
};
#endif