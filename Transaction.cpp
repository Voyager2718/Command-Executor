#include"Transaction"

void Transaction::AddCommand(ACommand command){
    commands.push_back(command);
}