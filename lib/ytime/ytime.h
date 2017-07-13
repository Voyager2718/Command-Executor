#include<string>
#include<iomanip>
#include<ctime>
#include<sstream>

using std::string;
using std::time_t;
using std::tm;
using std::put_time;
using std::time;
using std::localtime;
using std::stringstream;

namespace ytime{
    string GetTime();
}