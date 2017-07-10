#include"AValidator.h"
#include<map>
#include<string>
#include"Result.h"

using std::map;
using std::string;

string AValidator::getSuccessDescription(){
    return successDescription;
}

string AValidator::getExceptionDescription(){
    return exceptionDescription;
}

map<string, string> AValidator::getValuesMap(){
    return values;
}