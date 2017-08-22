#ifndef PARSER_H
#define PARSER_H

#include <string>

#include <list>

#include <memory>

#include "../Executor/Executor.h"

using std::string;

using std::list;

using std::shared_ptr;

class Parser
{
  protected:
    list<string> exceptions;

  public:
    /**
      * Parse should return either a shared_ptr<Executor> or a nullptr.
      * A nullptr indicates parse failure.
      */
    shared_ptr<Executor> Parse(string fileToParse);

    list<string> GetExceptions();
};

#endif