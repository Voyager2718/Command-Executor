#include "Command.h"

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
Result Command::Run(vector<string> arguments)
{
    if (command == "")
    {
        (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString("CMD-0002", "Command"), FAILED);
        return FAILED;
    }

    pid_t pid;
    int status;
    int fd[2];

    pipe(fd);

    if ((pid = fork()) < 0)
    {
        (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString("FORK-0001", "Command"), FAILED);
        return FAILED;
    }
    else if (pid == 0)
    {
        close(fd[0]);
        bool execStatus = false;
        if (execlp(command.c_str(), NULL) != 0)
        {
            execStatus = true;
            write(fd[1], &execStatus, sizeof(bool));
            exit(FAILED);
        }
    }
    else
    {
        wait(&status);

        bool execIsFailed = false;
        close(fd[1]);
        execIsFailed = read(fd[0], &execIsFailed, sizeof(bool));

        if (execIsFailed)
        {
            (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString("EXEC-0001", "Command"), FAILED);
            return FAILED;
        }
        else if (WEXITSTATUS(status) != 0)
        {
            (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString("CMD-0001", "Command"), FAILED);
            return FAILED;
        }
        else
        {
            (Report::GetInstance()).AddReport((ReportString::GetInstance()).GetReportString("SUCC-0001", "Command"), SUCCESSFUL);
            return SUCCESSFUL;
        }
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