#ifndef ISTDOUTCHECKER_H
#define ISTDOUTCHECKER_H

#include "./AOutputChecker.h"

class IStdoutChecker : public AOutputChecker
{
  public:
    virtual Result Check(string allOutput) override = 0;
};

#endif