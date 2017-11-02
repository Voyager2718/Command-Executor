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

    if ((pid = fork()) < 0)
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

        dup2(stdoutfd[1], STDOUT_FILENO);
        dup2(stderrfd[1], STDERR_FILENO);

        close(stdoutfd[0]);
        close(stdoutfd[1]);

        close(stderrfd[0]);
        close(stderrfd[1]);

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

        char buffer[DEFAULT_BUFFER_SIZE];
        FILE *out, *err;

        close(stdoutfd[1]);
        close(stderrfd[1]);

        out = fdopen(stdoutfd[0], "r");
        err = fdopen(stderrfd[0], "r");

        string outStr, errStr;

        while (fgets(buffer, sizeof(buffer), out))
        {
            string tmp(buffer);
            outStr += tmp;
        }

        while (fgets(buffer, sizeof(buffer), err))
        {
            string tmp(buffer);
            errStr += tmp;
        }

        for (auto stdoutChecker : stdoutCheckers)
        {
            switch (stdoutChecker->Check(outStr))
            {
            case SUCCESSFUL:
                (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString(SUCCESS, stdoutChecker->GetLastReportNumber(), stdoutChecker->GetSuccessDescription(), "StdOutputChecker"), SUCCESSFUL);
                break;
            case IGNORED:
                (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString(INFO, stdoutChecker->GetLastReportNumber(), stdoutChecker->GetIgnoredDescription(), "StdOutputChecker"), IGNORED);
                break;
            case FAILED:
                (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString(FATAL, stdoutChecker->GetLastReportNumber(), stdoutChecker->GetFatalDescription(), "StdOutputChecker"), FAILED);
                break;
            }
        }

        for (auto stderrChecker : stderrCheckers)
        {
            switch (stderrChecker->Check(errStr))
            {
            case SUCCESSFUL:
                (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString(SUCCESS, stderrChecker->GetLastReportNumber(), stderrChecker->GetSuccessDescription(), "ErrOutputChecker"), SUCCESSFUL);
                break;
            case IGNORED:
                (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString(INFO, stderrChecker->GetLastReportNumber(), stderrChecker->GetIgnoredDescription(), "ErrOutputChecker"), IGNORED);
                break;
            case FAILED:
                (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString(FATAL, stderrChecker->GetLastReportNumber(), stderrChecker->GetFatalDescription(), "ErrOutputChecker"), FAILED);
                break;
            }
        }

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

void Command::AddStdoutChecker(shared_ptr<IStdoutChecker> stdoutChecker)
{
    stdoutCheckers.push_back(stdoutChecker);
}

void Command::AddStderrChecker(shared_ptr<IStderrChecker> stderrChecker)
{
    stderrCheckers.push_back(stderrChecker);
}

void Command::AddValidator(shared_ptr<AValidator> validator)
{
    validators.push_back(validator);
}

string Command::GetDescription()
{
    return description;
}