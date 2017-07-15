#include"Transaction.h"

void Transaction::AddCommand(shared_ptr<Command> command){
    commands.push_back(command);
}

Result Transaction::Run(vector<string> params){
    bool haveIgnored = false;
    for(auto i : commands){
        Result result = i->Run(params);
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