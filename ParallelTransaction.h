#include<list>
#include<map>
#include<string>
#include"ParallelCommand.h"
#include"ATransaction.h"

using std::list;
using std::map;
using std::string;

class ParallelTransaction : public ATransaction{
protected:
    list<ParallelCommand> commands;
public:
    virtual void AddCommand(ParallelCommand command);

    virtual void Run(vector<string> params = vector<string>()) override;
};