#ifndef ATRANSACTION_H
#define ATRANSACTION_H

#include<list>
#include<map>
#include<string>
#include"IRunnable.h"
#include"ACommand.h"

using std::list;
using std::map;
using std::string;

class ATransaction : public IRunnable{
protected:
    string description;
    list< map< string, string > > values
public:
    Transaction();

    Transaction(string description);

    virtual void Run(vector<string> params = vector<string>()) = 0;
};

#endifs