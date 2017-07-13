#ifdef _MSC_VER
    #include<windows.h>
    #include<Wincrypt.h>
#elif __GNUC__
    #include<fcntl.h>
    #include<unistd.h>
    #include<sys/types.h>
    #include<sys/stat.h>
#endif

#include<cassert>

using namespace std;

namespace yrandom{
    unsigned int Random(unsigned int min, unsigned int max);
}