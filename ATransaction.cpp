#include"Transaction.h"

ATransaction::ATransaction(string description, bool isParallel = false){
    this->description = description;
}

ATransaction::ATransaction(bool isParallel = false){ }

void ATransaction::Run(){
    // TODO
}

bool GetIsParallel(){
    return isParallel;
}

void SetIsParallel(bool isParallel){
    this->isParallel = isParallel;
}