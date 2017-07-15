#include"ATransaction.h"

#include<list>
#include<map>
#include<string>
#include<memory>
#include<functional>

#include"IRunnable.h"
#include"Command.h"
#include"Result.h"

using std::string;

using std::list;
using std::map;

using std::shared_ptr;
using std::function;

class Transaction : public ATransaction{
protected:
    list< shared_ptr<Command> > commands;
public:
    virtual void AddCommand(shared_ptr<Command> command);

    virtual Result Run(vector<string> params = vector<string>());
};