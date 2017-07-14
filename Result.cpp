#include"Result.h"

string ResultToString(Result result){
    switch(result){
        SUCCESSFUL: return "Successful"; break;
        FAILED: return "Failed"; break;
        IGNORED: return "Ignored"; break;
        default: return "Result error"; break;
    }
}