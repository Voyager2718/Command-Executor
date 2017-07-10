#include"Report.h"

Report& Report::GetInstance(){
    static Report instance;
    return instance;
}

void Report::AddReport(string report){
    reports.push_back({{"report", report}, {"timestamp", ytime::GetTime()}});
}

list< map<string, string> > Report::GetReports(){
    return reports;
}