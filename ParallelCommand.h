#include"Command.h"

class ParallelCommand : public Command{
public:
    virtual Result Run(vector<string> params = vector<string>()) override;
}