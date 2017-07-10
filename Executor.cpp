#include"Executor.h"

Executor::Executor(IRunnable runnable){
    AddRunnable(runnable);
}

void Executor::AddRunnable(IRunnable runnable){
    runnables.push_back(runnable);
}

/**
 * If there's one or more IGNORED, then return IGNROED after running all runnables.
 * If there's FAILED, stop running following runnables and return FAILED immediately.
 * If all runnables are run successfully, then return SUCCESSFUL.
*/
Result Executor::Execute(function<void()>succ = success, function<void()>fl = failed){
    bool haveIgnored = false;
    for(auto const& i : runnables){
        Result result = i.Run();
        if(result == IGNORED){
            haveIgnored = true;
        }
        if(result == FAILED){
            fl();
            return FAILED;
        }
    }
    succ();
    if(haveIgnored){
        return IGNORED;
    }
    return SUCCESSFUL;
}