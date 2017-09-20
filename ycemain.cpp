#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "src/Executor/Executor.h"
#include "src/Runnable/Command/Command.h"
#include "src/Runnable/IRunnable.h"
#include "src/Runnable/Transaction/ParallelTransaction/ParallelTransaction.h"
#include "src/Runnable/Command/ParallelCommand/ParallelCommand.h"
#include "src/Runnable/Transaction/Transaction.h"

using std::to_string;

int currentInstanceLock;

bool ReachedMaximumInstance()
{
    for (int i = 0;; i++)
    {
        int fd = open(("/tmp/yce_instance" + to_string(i) + ".lock").c_str(), O_RDONLY);
        if (fd > 0)
        {
            pid_t maybePid;
            read(fd, &maybePid, sizeof(maybePid));

            if (kill(maybePid, 0) == 0)
            {
                if (i >= MAX_INSTANCE - 1)
                {
                    cout << "[INFO] INIT-0001: Only " + to_string(MAX_INSTANCE) + " instance can be run at the same time.\nModify maximum instance at Settings.h and recompile. [ycemain]" << endl;
                    return true;
                }
                close(fd);
            }
            else if (errno == ESRCH)
            {
                remove(("/tmp/yce_instance" + to_string(i) + ".lock").c_str());

                currentInstanceLock = i;

                int fd2 = open(("/tmp/yce_instance" + to_string(i) + ".lock").c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
                pid_t currentPid = getpid();
                write(fd2, &currentPid, sizeof(currentPid));

                return false;
            }
            else
            {
                perror("[FATAL] INIT-0002: Unknown process status. [ycemain]");
            }
        }
        else
        {
            currentInstanceLock = i;

            int fd2 = open(("/tmp/yce_instance" + to_string(i) + ".lock").c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
            pid_t currentPid = getpid();
            write(fd2, &currentPid, sizeof(currentPid));

            return false;
        }
    }
}

int main(int argc, char *argv[])
{
    if (ReachedMaximumInstance())
    {
        return 1;
    }

    sleep(5);

    remove(("/tmp/yce_instance" + to_string(currentInstanceLock) + ".lock").c_str());
}