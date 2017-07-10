#include"Report.h"

Report& Report::GetInstance(){
    static Report instance;
    return instance;
}

void Report::AddReport(string report, Result result = SUCCESSFUL){
    reports.push_back({{"report", report}, {"timestamp", ytime::GetTime()}, {"result", result}});
}

list< map<string, string> > Report::GetReports(){
    return reports;
}

void Report::PrintReport(function<void(string, string, string)> = printer){
    for(auto r : reports){
        printer(r["timestamp"], r["result"], r["report"]);
    }
}

void Report::PrintSuccessfulReport(function<void(string, string, string)> = printer){
    for(auto r : reports){
        if(r["result"] == FAILED){
            printer(r["timestamp"], r["result"], r["report"]);
        }
    }
}

void Report::PrintFailedReport(function<void(string, string, string)> = printer){
    for(auto r : reports){
        if(r["result"] == SUCCESSFUL){
            printer(r["timestamp"], r["result"], r["report"]);
        }
    }
}

void Report::Printer(string timestamp, string result, string report){
    cout<<r["timestamp"]<<" - "<<r["result"]<<r["report"]<<endl;
}