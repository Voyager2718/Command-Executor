#include"ytime.h"

namespace ytime{
    string GetTime(){
        time_t t = time(nullptr);
        tm tm = *localtime(&t);
        stringstream ss;
        ss<<put_time(&tm, "%c %Z");
        return ss.str();
    }
}