#ifndef RESULT_H
#define RESULT_H

#include <string>

using std::string;

enum Result
{
    SUCCESSFUL,
    FAILED,
    IGNORED
};

string ResultToString(Result result);

#endif