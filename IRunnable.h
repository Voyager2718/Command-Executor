#ifndef IRUNNABLE_H
#define IRUNNABLE_H

#include<vector>

using std::vector;

class IRunnable{
public:
    virtual Result Run(vector<string> params = vector<string>()) = 0;
};

#endif