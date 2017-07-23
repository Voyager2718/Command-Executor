#ifndef ATRANSACTION_H
#define ATRANSACTION_H

#include <list>
#include <map>
#include <string>

#include <memory>

#include "../../Result/Result.h"
#include "../IRunnable.h"

using std::list;
using std::map;
using std::string;

using std::vector;

using std::shared_ptr;

class ATransaction : public IRunnable
{
  protected:
    string description;
    list<map<string, string>> values;

  public:
    ATransaction();

    ATransaction(string description);
    
    virtual Result Run(vector<string> arguments = vector<string>()) = 0;
};

#endif