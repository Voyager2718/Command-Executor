#include"Command.h"

Command::Command(int timeout, string description){
    this->timeout = timeout;
    this->description = description;
}

Command::Command(){ }

Result Run(vector<string> params = vector<string>()){
    // TODO
}

void Command::SetTimeout(int timeout){
    this->timeout = timeout;
}

int Command::GetTimeout(){
    return timeout;
}

void Command::AddValidator(IValidator validator){
    validators.push_back(validator);
}

void Command::AddOutputChecker(IOutputChecker outputChecker){
    outputCheckers.push_back(outputChecker);
}

string Command::GetDescription(){
    return description;
}