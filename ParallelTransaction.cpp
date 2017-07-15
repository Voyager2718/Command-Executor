#include"ParallelTransaction.h"

void ParallelTransaction::AddCommand(shared_ptr<ParallelCommand> command){
    commands.push_back(command);
}

Result ParallelTransaction::Run(vector<string> params){
    bool haveIgnored = false;

    pid_t pid;
    unsigned int numberOfRunningProcess = 0;
    int status;
    
    for(auto c : commands){
        if((pid = fork()) < 0){
            (Report::GetInstance()).AddReport("[FATAL] FORK-0001: Unable to create new process. [ParallelTransaction]", FAILED);
            return FAILED;
        }else if(pid == 0){
            return c->Run(params);
        }else{
            if(++numberOfRunningProcess >= MAX_PROCESS){
                int returnValue = wait(&status);
                Result result = (Result)WEXITSTATUS(returnValue);
                if(result == IGNORED){
                    haveIgnored = true;
                }
                if(result == FAILED){
                    return FAILED; 
                }
            }
        }
    }

    for(int i = 0; i < MAX_PROCESS - 1; i++){
        int returnValue = wait(&status);
        Result result = (Result)WEXITSTATUS(returnValue);
        if(result == IGNORED){
            haveIgnored = true;
        }  
        if(result == FAILED){
            return FAILED; 
        }
    }

    if(haveIgnored){
        return IGNORED;
    }
    return SUCCESSFUL;
}