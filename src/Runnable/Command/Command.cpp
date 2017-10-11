#include "Command.h"

#include <sys/socket.h>

Command::Command(string command)
{
    SetCommand(command);
}

Command::Command(string command, int timeout, string description)
{
    SetCommand(command);
    SetTimeout(timeout);

    this->description = description;
}

Command::Command(int timeout, string description)
{
    SetTimeout(timeout);

    this->description = description;
}

Command::Command()
{
    description = "Command.cpp";
}

// FIXME: Add IValidator and IOutputChecker.
Result Command::Run(vector<string> arguments, bool printoutputFd)
{
    if (command == "")
    {
        (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString("CMD-0002", "Command"), FAILED);
        return FAILED;
    }

    pid_t pid;

    int exitStatus;

    bool execFailed = false;

    int stdoutfd[2], stderrfd[2], execStatus[2];

    if (pipe(stdoutfd) || pipe(stderrfd) || pipe(execStatus))
    {
        (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString("PIPE-0001", "Command"), FAILED);
        return FAILED;
    }

    if ((pid = vfork()) < 0)
    {
        (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString("FORK-0001", "Command"), FAILED);
        return FAILED;
    }
    else if (pid == 0)
    {
        const char **args = (const char **)malloc(sizeof(char) * (arguments.size() + 2));
        args[0] = command.c_str();

        for (int i = 1; i < arguments.size() + 1; i++)
        {
            args[i] = arguments[i - 1].c_str();
        }

        args[arguments.size() + 1] = (char *)0;

        if (execvp(command.c_str(), (char *const *)args))
        {
            execFailed = true;
            close(execStatus[0]);
            write(execStatus[1], &execFailed, sizeof(bool));
            exit(1);
        }
    }
    else
    {
        waitpid(pid, &exitStatus, 0);

        close(execStatus[1]);
        read(execStatus[0], &execFailed, sizeof(bool));

        if (execFailed)
        {
            (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString("EXEC-0001", "Command"), FAILED);
            return FAILED;
        }

        if (WEXITSTATUS(exitStatus))
        {
            (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString("CMD-0001", "Command"), FAILED);
            return FAILED;
        }

        (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString("SUCC-0001", "Command"), SUCCESSFUL);
        return SUCCESSFUL;
    }
    return FAILED;
}

void Command::SetCommand(string command)
{
    this->command = command;
}

string Command::GetCommand()
{
    return command;
}

void Command::SetTimeout(int timeout)
{
    this->timeout = timeout;
}

int Command::GetTimeout()
{
    return timeout;
}

void Command::AddValidator(shared_ptr<AValidator> validator)
{
    validators.push_back(validator);
}

void Command::AddOutputChecker(shared_ptr<AOutputChecker> outputChecker)
{
    outputCheckers.push_back(outputChecker);
}

string Command::GetDescription()
{
    return description;
}