#ifndef TRANSACTION_H
#define TRANSACTION_H

#include<list>
#include<map>
#include<string>
#include"IRunnable.h"
#include"ACommand.h"

using std::list;
using std::map;
using std::string;

class Transaction : public IRunnable{
private:
    list<ACommand> commands;
    string description;
    bool isParallel;
    list< map< string, string > > values
public:
    ATransaction(bool isParallel = false);

    ATransaction(string description, bool isParallel = false);

    virtual void Run(vector<string> params = vector<string>());

    bool GetIsParallel();

    void SetIsParallel(bool isParallel);
};

#endifs