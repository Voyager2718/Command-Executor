#include "Executor.h"

void Executor::success()
{
    (Report::GetInstance()).PrintReport();
}

void Executor::fail()
{
    (Report::GetInstance()).PrintReport();
}

Executor::Executor() {}

Executor::Executor(shared_ptr<IRunnable> runnable)
{
    AddRunnable(runnable);
}

void Executor::AddRunnable(shared_ptr<IRunnable> runnable)
{
    runnables.push_back(runnable);
}

Result Executor::Execute()
{
    return Execute(success, fail);
}

/**
 * If there's one or more IGNORED, then return IGNROED after running all runnables.
 * If there's FAILED, stop running following runnables and return FAILED immediately.
 * If all runnables are run successfully, then return SUCCESSFUL.
*/
Result Executor::Execute(function<void()> succ, function<void()> fl, vector<string> arguments)
{
    bool haveIgnored = false;
    for (auto r : runnables)
    {
        Result result = r->Run(arguments);
        if (result == IGNORED)
        {
            haveIgnored = true;
        }
        if (result == FAILED)
        {
            fl();
            return FAILED;
        }
    }
    succ();
    if (haveIgnored)
    {
        return IGNORED;
    }
    return SUCCESSFUL;
}

Result Executor::Execute(vector<string> arguments, function<void()> succ, function<void()> fl)
{
    return Execute(succ, fl, arguments);
}