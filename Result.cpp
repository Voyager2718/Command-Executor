#include"Result.h"

string ResultToString(Result result){
    switch(result){
        case SUCCESSFUL: return "Successful"; break;
        case FAILED: return "Failed"; break;
        case IGNORED: return "Ignored"; break;
        default: return "Result error"; break;
    }
}