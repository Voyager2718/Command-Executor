#include"ParallelTransaction.h"

void ParallelTransaction::AddCommand(shared_ptr<ParallelCommand> command){
    commands.push_back(command);
}

