#include "ReportString.h"

ReportString &ReportString::GetInstance()
{
    static ReportString instance;
    return instance;
}

/**
  * Return 0 if successful, return non 0 otherwise.
  */
int ReportString::AddReportString(ReportType type, string reportno, string description)
{
    if (reportStrings.find(reportno) == reportStrings.end())
    {
        string s_type = "";
        switch (type)
        {
        case FATAL:
            s_type += "FATAL";
            break;
        case WARNING:
            s_type += "WARNING";
            break;
        case INFO:
            s_type += "INFO";
            break;
        case SUCCESS:
            s_type += "SUCC";
            break;
        }
        reportStrings[reportno] = "[" + s_type + "] " + reportno + ": " + description + " ";
        return 0;
    }
    else
    {
        return 1;
    }
}

string ReportString::GetReportString(string reportno, string fromFile)
{
    return (reportStrings[reportno] + "[" + fromFile + "]");
}

string ReportString::GetReportString(ReportType type, string reportno, string description, string fromFile)
{
    string tmp = "";

    switch (type)
    {
    case FATAL:
        tmp += "FATAL";
        break;
    case WARNING:
        tmp += "WARNING";
        break;
    case INFO:
        tmp += "INFO";
        break;
    case SUCCESS:
        tmp += "SUCC";
        break;
    }

    tmp = "[" + tmp + "] " + reportno + ": " + description + " [" + fromFile + "]";

    return tmp;
}

ReportString::ReportString()
{
    AddReportString(SUCCESS, "SUCC-0001", "Process execution successful.");

    AddReportString(FATAL, "INIT-0001", "Reached maximum instance restriction.");

    AddReportString(FATAL, "CMD-0001", "Command execution failed.");
    AddReportString(FATAL, "CMD-0002", "Command not set.");

    AddReportString(FATAL, "EXEC-0001", "Cannot execute command.");

    AddReportString(FATAL, "PIPE-0001", "Cannot create pipe.");

    AddReportString(FATAL, "FORK-0001", "Unable to create new process.");

    AddReportString(SUCCESS, "OUTPUT-0001", "Output checker has successfully checked output.");
    AddReportString(INFO, "OUTPUT-0002", "Output checker has checked output, with some ignorable exceptions.");
    AddReportString(FATAL, "OUTPUT-0003", "Output checker has found incorrect outputs.");
}