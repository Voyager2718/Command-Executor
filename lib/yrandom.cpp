#include"yrandom.h"

namespace yrandom{
    int Random(int min, int max){
        srand(time(NULL));
        return static_cast<int>(rand() % max + min);
    }
}