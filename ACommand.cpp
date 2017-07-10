#include"ACommand.h"

ACommand::ACommand(int timeout, string description){
    this->timeout = timeout;
    this->description = description;
}

ACommand::ACommand(){ }

void ACommand::SetTimeout(int timeout){
    this->timeout = timeout;
}

int ACommand::GetTimeout(){
    return timeout;
}

void ACommand::AddValidator(IValidator validator){
    validators.push_back(validator);
}

void ACommand::AddOutputChecker(IOutputChecker outputChecker){
    outputCheckers.push_back(outputChecker);
}

string ACommand::GetDescription(){
    return description;
}