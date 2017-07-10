#ifndef TRANSACTION_H
#define TRANSACTION_H

#include<list>
#include<map>
#include<string>
#include"ACommand.h"

using std::list;
using std::map;
using std::string;

class Transaction{
private:
    list<ACommand> commands;
    string description;
    bool isParallel;
    list< map< string, string > > values
public:
    ATransaction(bool isParallel = false);

    ATransaction(string description, bool isParallel = false);

    virtual void Run();

    bool GetIsParallel();

    void SetIsParallel(bool isParallel);
};

#endifs