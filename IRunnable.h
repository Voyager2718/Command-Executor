#ifndef IRUNNABLE_H
#define IRUNNABLE_H

class IRunnable{
public:
    IRunnable() = default;

    virtual ~IRunnable() = default;

    virtual IRunnable(const IRunnable& runnable) = default;

    virtual Result Run() = 0;
};

#endif