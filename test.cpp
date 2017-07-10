#include<iostream>
#include"Report.h"
#include<map>
#include<list>

using namespace std;

int main(){
    Report report = Report::GetInstance();

    report.AddReport("My report test");

    list< map <string, string> > r = report.GetReports();
    for(auto& i : r){
        cout<< i["timestamp"] << "-" << i["report"] <<endl;
    }
}