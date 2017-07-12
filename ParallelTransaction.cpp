#include"ParallelTransaction.h"

void ParallelTransaction::AddCommand(ParallelCommand command){
    commands.push_back(command);
}