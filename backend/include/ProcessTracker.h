#pragma once
#include <string>
#include "DataLogger.h"

class ProcessTracker {
public:
    static void printAllProcesses();
    static std::vector<ProcessRecord> collectProcesses();
};
