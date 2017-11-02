#include <iostream>
#include <memory>

#include "src/Executor/Executor.h"
#include "src/Runnable/Command/Command.h"
#include "src/Runnable/IRunnable.h"
#include "src/Runnable/Transaction/ParallelTransaction/ParallelTransaction.h"
#include "src/Runnable/Command/ParallelCommand/ParallelCommand.h"
#include "src/Runnable/Transaction/Transaction.h"

using std::cout;
using std::cin;
using std::endl;

using std::shared_ptr;
using std::make_shared;

#include "src/OutputChecker/IStdoutChecker.h"

class stdouttest : public IStdoutChecker
{
    Result Check(string allOutput)
    {
        cout << "Output Checker: " << allOutput;
        return SUCCESSFUL;
    }

    string GetSuccessDescription() { return "Succ"; }

    string GetFatalDescription() { return "Fatal"; }

    string GetIgnoredDescription() { return "Ignored"; }

    string GetLastReportNumber() { return "TEST-0001"; }
};

int main(int argc, char *argv[])
{
    Executor executor;
    shared_ptr<ParallelTransaction> transaction = make_shared<ParallelTransaction>();

    shared_ptr<ParallelCommand> tmp = make_shared<ParallelCommand>("./test_programs/print1");

    tmp->AddStdoutChecker(make_shared<stdouttest>());

    transaction->AddCommand(tmp);
    transaction->AddCommand(make_shared<ParallelCommand>("./test_programs/print2"));

    executor.AddRunnable(transaction);

    executor.Execute();
    return 0;
}