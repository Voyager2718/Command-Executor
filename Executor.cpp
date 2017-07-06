#include"Executor.h"
#include"Result.h"

Executor::Executor(ACommand command){
    commands.push_back(command);
}

/**
 * If there's one or more IGNORED, then return IGNROED after running all commands.
 * If there's EXCEPTION, stop running following commands and return EXCEPTION immediately.
 * If all commands are run successfully, then return SUCCESSFUL.
*/
Result Executor::Execute(){
    bool haveIgnored = false;
    for(auto const& i : commands){
        Result result = i.Run();
        if(result == IGNORED){
            haveIgnored = true;
        }
        if(result == EXCEPTION){
            return EXCEPTION;
        }
    }
    return SUCCESSFUL;
}