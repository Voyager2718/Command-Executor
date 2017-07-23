#include <iostream>
#include <memory>

#include "src/Executor/Executor.h"
#include "src/Runnable/Command/Command.h"
#include "src/Runnable/IRunnable.h"
#include "src/Runnable/Transaction/ParallelTransaction/ParallelTransaction.h"
#include "src/Runnable/Command/ParallelCommand/ParallelCommand.h"

using std::cout;
using std::cin;
using std::endl;

using std::shared_ptr;
using std::make_shared;

int main(int argc, char *argv[])
{
    Executor executor;
    shared_ptr<Transaction> pTransaction = make_shared<ParallelTransaction>();

    pTransaction->AddCommand(make_shared<ParallelCommand>());
    pTransaction->AddCommand(make_shared<ParallelCommand>());

    executor.AddRunnable(pTransaction);

    executor.Execute();
    return 0;
}