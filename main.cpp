#include<iostream>
#include<memory>

#include"Executor.h"
#include"Command.h"
#include"IRunnable.h"

using std::cout;
using std::cin;
using std::endl;

using std::shared_ptr;
using std::make_shared;

int main(int argc, char* argv[]){
    Executor executor;
    shared_ptr<IRunnable> command = make_shared<Command>();
    executor.AddRunnable(command);
    executor.Execute();
    return 0;
}