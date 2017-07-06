#ifndef REPORT_H
#define REPORT_H

#include<memory>

using std::shared_ptr;

class Report{
private:
    static shared_ptr<Report> instance;
    Report(){}
public:
    static shared_ptr<Report> getInstance(){
        static Report instance;
        return make_shared<Report>();
    }
};

#endif