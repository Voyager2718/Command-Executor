#include "ParallelTransaction.h"

void ParallelTransaction::AddCommand(shared_ptr<ParallelCommand> command)
{
    commands.push_back(command);
}

Result ParallelTransaction::Run(vector<string> arguments, bool printOutputs)
{
    bool haveIgnored = false;

    ThreadPool pool(MAX_THREADS);
    list<future<Result>> results;

    for (auto command : commands)
    {
        results.push_back(
            pool.enqueue([command, arguments] {
                return command->Run(arguments);
            }));
    }

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

    if (haveIgnored)
    {
        return IGNORED;
    }

    return SUCCESSFUL;
}