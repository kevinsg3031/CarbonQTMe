#include "ContextSwitchAnalyzer.h"
#include <fstream>
#include <string>

using namespace std;

void ContextSwitchAnalyzer::getContextSwitches(
    const string& pid,
    long& voluntary,
    long& nonVoluntary
) {
    ifstream file("/proc/" + pid + "/status");
    string line;
    voluntary = nonVoluntary = 0;
    while (std::getline(file, line)) {
        try {
            if (line.rfind("voluntary_ctxt_switches:", 0) == 0)
                voluntary = std::stol(line.substr(26));
            else if (line.rfind("nonvoluntary_ctxt_switches:", 0) == 0)
                nonVoluntary = std::stol(line.substr(30));
        } catch (...) {
            
        }
    }
}
