#include"Command.h"

Command::Command(int timeout, string description){
    this->timeout = timeout;
    this->description = description;

    Command();
}

Command::Command(){
    #if defined _MSC_VER
        command = "./test";
    #elif defined __GNUC__
        command = "./test";
    #else
        command = "./test";
    #endif
    description = "Command.cpp";
}

// FIXME: Add IValidator and IOutputChecker.
Result Command::Run(vector<string> params){
    pid_t pid;
    int status;
    int fd[2];

    pipe(fd);

    if((pid = fork()) < 0){
        (Report::GetInstance()).AddReport("[FATAL] FORK-0001: Unable to create new process.", FAILED);
        return FAILED;
    }else if(pid == 0){
        close(fd[0]);
        bool execStatus = false;
        if(execlp(command.c_str(), NULL) != 0){
            execStatus = true;
            write(fd[1], &execStatus, sizeof(bool));
        }
    }else{
        wait(&status);
        bool execIsFailed = false;
        close(fd[1]);
        execIsFailed = read(fd[0], &execIsFailed, sizeof(bool));
        
        if(WEXITSTATUS(status) != 0){   
            (Report::GetInstance()).AddReport("[FATAL] CMD-0001: Command execution failed.", FAILED);
            return FAILED;
        }else if(execIsFailed){
            (Report::GetInstance()).AddReport("[FATAL] EXEC-0001: Cannot execute command.", FAILED);
            return FAILED;
        }else{
            (Report::GetInstance()).AddReport("[SUCC]: Process execution successful.", SUCCESSFUL);
            return SUCCESSFUL;
        }
    }
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