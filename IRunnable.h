#ifndef IRUNNABLE_H
#define IRUNNABLE_H

#include<vector>
#include<string>
#include"Result.h"

using std::vector;
using std::string;

class IRunnable{
public:
    virtual Result Run(vector<string> params = vector<string>()) = 0;
};

#endif