#include "SystemMonitor.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

static std::vector<long> readCpuTimes() {
    ifstream file("/proc/stat");
    string line;
    std::vector<long> times;

    while (getline(file, line)) {
        if (line.rfind("cpu", 0) == 0 && line != "cpu") {
            istringstream ss(line);
            string cpu;
            long user, nice, system, idle;
            ss >> cpu >> user >> nice >> system >> idle;
            times.push_back(user + nice + system);
            times.push_back(idle);
        }
    }
    return times;
}

std::vector<double> SystemMonitor::getCpuUsagePerCore() {
    auto t1 = readCpuTimes();
    this_thread::sleep_for(chrono::milliseconds(200));
    auto t2 = readCpuTimes();

    std::vector<double> usage;
    for (size_t i = 0; i < t1.size(); i += 2) {
        long busy = t2[i] - t1[i];
        long idle = t2[i + 1] - t1[i + 1];
        usage.push_back(100.0 * busy / (busy + idle));
    }
    return usage;
}

void SystemMonitor::getMemoryUsage(double& usedMB, double& swapUsedMB) {
    ifstream file("/proc/meminfo");
    string key;
    long value;
    long memTotal=0, memFree=0, swapTotal=0, swapFree=0;

    while (file >> key >> value) {
        if (key == "MemTotal:") memTotal = value;
        if (key == "MemAvailable:") memFree = value;
        if (key == "SwapTotal:") swapTotal = value;
        if (key == "SwapFree:") swapFree = value;
    }

    usedMB = (memTotal - memFree) / 1024.0;
    swapUsedMB = (swapTotal - swapFree) / 1024.0;
}

double SystemMonitor::getRamUsage()
{
    std::ifstream file("/proc/meminfo");
    std::string key;
    long value;
    std::string unit;
    long total = 0;
    long available = 0;

    while (file >> key >> value >> unit)
    {
        if (key == "MemTotal:")
            total = value;

        if (key == "MemAvailable:")
        {
            available = value;
            break;
        }
    }

    if (total == 0)
        return 0;

    return ((total - available) / (double)total) * 100.0;
}
