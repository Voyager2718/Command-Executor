#include"AOutputChecker.h"
#include<map>
#include<string>

using std::map;
using std::string;

Result AOutputChecker::Check(){

}

string AOutputChecker::getSuccessDescription(){
    return successDescription;
}

string AOutputChecker::getExceptionDescription(){
    return exceptionDescription;
}

map<string, string> getValuesMap(){
    return values;
}