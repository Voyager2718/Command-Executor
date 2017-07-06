#include"ACommand.h"

ACommand::ACommand(int timeOut, string description){
    this->timeOut = timeOut;
    this->description = description;
}

void ACommand::SetTimeout(int timeOut){
    this->timeOut = timeOut;
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