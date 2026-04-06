#pragma once
#include <string>

using namespace std;

class ContextSwitchAnalyzer {
public:
    static void getContextSwitches(
        const string& pid,
        long& voluntary,
        long& nonVoluntary
    );
};

