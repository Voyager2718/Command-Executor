#include<iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[]){
    for(auto const& arg : argv){
        cout<<arg<<endl;
    }
    return 127;
}