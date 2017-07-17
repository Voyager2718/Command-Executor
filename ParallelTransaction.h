#include <list>
#include <map>
#include <string>
#include <memory>

#include "ParallelCommand.h"
#include "ATransaction.h"
#include "Settings.h"

using std::list;
using std::map;
using std::string;

using std::shared_ptr;

class ParallelTransaction : public ATransaction
{
  protected:
    list<shared_ptr<ParallelCommand>> commands;

  public:
    virtual void AddCommand(shared_ptr<ParallelCommand> command);

    virtual Result Run(vector<string> params = vector<string>()) override;
};