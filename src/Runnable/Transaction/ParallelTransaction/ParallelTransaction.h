#include <list>
#include <map>
#include <string>
#include <memory>

#include <future>

#include "../../Command/ParallelCommand/ParallelCommand.h"
#include "../ATransaction.h"
#include "../../../../Settings.h"

#include "../../../../lib/ThreadPool/ThreadPool.h"
#include "../../../Result/Result.h"

using std::list;
using std::map;
using std::string;

using std::shared_ptr;

using std::future;

class ParallelTransaction : public ATransaction
{
  protected:
    list<shared_ptr<ParallelCommand>> commands;

  public:
    virtual void AddCommand(shared_ptr<ParallelCommand> command);

    virtual Result Run(vector<string> arguments = vector<string>(), bool printOutputs = false) override;
};