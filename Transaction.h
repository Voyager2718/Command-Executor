#include"ATransaction.h"

#include<list>
#include<map>
#include<string>
#include"IRunnable.h"
#include"ACommand.h"

using std::list;
using std::map;
using std::string;

class Transaction : public ATransaction{
protected:
    list<ACommand> commands;
public:
    virtual void AddCommand(ACommand command);

    virtual void Run(vector<string> params = vector<string>()) override;
};