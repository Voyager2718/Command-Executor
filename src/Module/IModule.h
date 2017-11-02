#ifndef IMODULE_H
#define IMODULE_H

#include <string>
#include <vector>

#include "../Result/Result.h"

using std::string;
using std::vector;

class IModule
{
  public:
    virtual string GetModuleName() = 0;

    virtual string GetModuleDescription() = 0;

    virtual int GetModuleVersion() = 0;

    virtual Result Run(vector<string> arguments = vector<string>()) = 0;

    /*
     * [Experimental]
     * This function enables auto argument injection.
     */
    virtual Result Run(vector<string> dependencies, vector<string> arguments) = 0;
};

#endif