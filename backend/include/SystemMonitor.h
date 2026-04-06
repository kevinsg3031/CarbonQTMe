#pragma once
#include <vector>

using namespace std;

class SystemMonitor {
public:
    static vector<double> getCpuUsagePerCore();
    static void getMemoryUsage(double& usedMB, double& swapUsedMB);
    static double getRamUsage();
};
