#include <iostream>
#include <memory>

#include "Executor.h"
#include "Command.h"
#include "IRunnable.h"
#include "ParallelTransaction.h"
#include "ParallelCommand.h"

using std::cout;
using std::cin;
using std::endl;

using std::shared_ptr;
using std::make_shared;

int main(int argc, char *argv[])
{
    Executor executor;
    shared_ptr<ParallelTransaction> pTransaction = make_shared<ParallelTransaction>();
    pTransaction->AddCommand(make_shared<ParallelCommand>());
    pTransaction->AddCommand(make_shared<ParallelCommand>());
    executor.AddRunnable(pTransaction);
    executor.Execute();
    return 0;
}