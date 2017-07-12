#include<iostream>
#include"../lib/ytime.h"
#include"../lib/yrandom.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[]){
    int numberOfLines;
    if(argc > 1){
        if((numberOfLines = atoi(argv[1])) < 1){
            return 62;
        }
    }else{
        numberOfLines = 50;
    }

    int errorAtLine = yrandom::Random(0, numberOfLines - 1);

    for(int i = 0; i < numberOfLines; i++){
        cout<<"["<<ytime::GetTime()<<"] Normal output."<<endl;
        if(errorAtLine == i){
            cout<<"["<<ytime::GetTime()<<"] TEST-1234: Error output."<<endl;
        }
    }

    return 63;
}