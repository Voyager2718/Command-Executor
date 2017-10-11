#ifndef IRUNNABLE_H
#define IRUNNABLE_H

#include <vector>
#include <string>
#include <functional>

#include "../Result/Result.h"

using std::vector;
using std::string;

using std::function;

class IRunnable
{
  public:
    virtual Result Run(vector<string> arguments = vector<string>(), bool printOutputs = false) = 0;
};

#endif