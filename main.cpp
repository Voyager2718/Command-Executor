#include<iostream>
#include<memory>

#include"Executor.h"
#include"Command.h"
#include"IRunnable.h"
#include"Transaction.h"

using std::cout;
using std::cin;
using std::endl;

using std::shared_ptr;
using std::make_shared;

int main(int argc, char* argv[]){
    Executor executor;
    shared_ptr<Transaction> transaction = make_shared<Transaction>();
    transaction->AddCommand(make_shared<Command>());
    executor.AddRunnable(transaction);
    executor.Execute();
    return 0;
}