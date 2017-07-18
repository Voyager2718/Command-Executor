#include "ParallelTransaction.h"

void ParallelTransaction::AddCommand(shared_ptr<ParallelCommand> command)
{
    commands.push_back(command);
}

Result ParallelTransaction::Run(vector<string> params)
{
    bool haveIgnored = false;

    ThreadPool pool(MAX_THREADS);
    list<future<Result>> results;

    for (auto command : commands)
    {
        results.push_back(
            pool.enqueue([command, params] {
                return command->Run(params);
            }));
        /*
        if (results.back().get() == IGNORED)
        {
            haveIgnored = true;
        }
        */
        if (results.back().get() == FAILED)
        {
            return FAILED;
        }
    }

    if (haveIgnored)
    {
        return IGNORED;
    }

    return SUCCESSFUL;
}