#include"Command.h"

Command::Command(int timeout, string description){
    this->timeout = timeout;
    this->description = description;

    Command();
}

Command::Command(){
    #if defined _MSC_VER
        command = "echo \"Windows Command Executor.\"";
    #elif defined __GNUC__
        command = "echo \"Linux Command Executor.\"";
    #else
        command = "echo \"Command Executor.\"";
    #endif
}

// FIXME: Add IValidator and IOutputChecker.
Result Command::Run(vector<string> params){
    pid_t pid;
    int returnValue;

    if((pid = fork()) < 0){
        (Report::GetInstance()).AddReport("[FATAL] CMD-0001: Unable to create new process.", FAILED);
        return FAILED;
    }else if(pid == 0){
        execl(command.c_str(), NULL);
    }

    wait(&returnValue);
    if(returnValue != 0){
        (Report::GetInstance()).AddReport("[FATAL] CMD-0002: Process execution failed.", FAILED);
    }else{
        return SUCCESSFUL;
    }
    return SUCCESSFUL;
}

void Command::SetCommand(string command){
    this->command = command;
}

string Command::GetCommand(){
    return command;
}

void Command::SetTimeout(int timeout){
    this->timeout = timeout;
}

int Command::GetTimeout(){
    return timeout;
}

void Command::AddValidator(shared_ptr<AValidator> validator){
    validators.push_back(validator);
}

void Command::AddOutputChecker(shared_ptr<AOutputChecker> outputChecker){
    outputCheckers.push_back(outputChecker);
}

string Command::GetDescription(){
    return description;
}