#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "lib/InstanceRestriction/instance_restriction.h"

#include "src/ReportString/ReportString.h"
#include "src/Executor/Executor.h"
#include "src/Runnable/Command/Command.h"
#include "src/Runnable/IRunnable.h"
#include "src/Runnable/Transaction/ParallelTransaction/ParallelTransaction.h"
#include "src/Runnable/Command/ParallelCommand/ParallelCommand.h"
#include "src/Runnable/Transaction/Transaction.h"

using std::to_string;

int currentInstanceLock;

int main(int argc, char *argv[])
{
    if (ReachedMaximumInstance())
    {
        (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString("INIT-0001", "ycemain"), FAILED);
        return 0;
    }
}