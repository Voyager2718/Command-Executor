#ifndef ISTDERRCHECKER_H
#define ISTDERRCHECKER_H

#include "./AOutputChecker.h"

class IStderrChecker : public AOutputChecker
{
  public:
    virtual Result Check(string allOutput) override = 0;
};

#endif