#include"Report.h"

map<string, string> MakeMap(string a, string b){
    map<string, string> m;
    m.insert(std::pair<string, string>(a,b));
    return m;
}

Report& Report::GetInstance(){
    static Report instance;
    return instance;
}

void Report::AddReport(string report, Result result){
    map<string, string> mp = {
        {"timestamp", ytime::GetTime()},
        {"result", ResultToString(result)},
        {"report", report}
    };
    reports.push_back(mp);
}

list< map<string, string> > Report::GetReports(){
    return reports;
}

void Report::PrintReport(function<void(string, string, string)> printer){
    for(auto r : reports){
        printer(r["timestamp"], r["result"], r["report"]);
    }
}

void Report::PrintSuccessfulReport(function<void(string, string, string)> printer){
    for(auto r : reports){
        if(r["result"] == ResultToString(SUCCESSFUL)){
            printer(r["timestamp"], r["result"], r["report"]);
        }
    }
}

void Report::PrintFailedReport(function<void(string, string, string)> printer){
    for(auto r : reports){
        if(r["result"] == ResultToString(FAILED) or r["result"] == ResultToString(IGNORED)){
            printer(r["timestamp"], r["result"], r["report"]);
        }
    }
}

void Report::Printer(string timestamp, string result, string report){
    cout<<timestamp<<" - "<<result<<" - "<<report<<endl;
}