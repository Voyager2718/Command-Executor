#ifndef ATRANSACTION_H
#define ATRANSACTION_H

#include <list>
#include <map>
#include <string>

#include "Result.h"
#include "IRunnable.h"

using std::list;
using std::map;
using std::string;

using std::vector;

class ATransaction : public IRunnable
{
  protected:
    string description;
    list<map<string, string>> values;

  public:
    ATransaction();

    ATransaction(string description);

    virtual Result Run(vector<string> params = vector<string>()) = 0;
};

#endif