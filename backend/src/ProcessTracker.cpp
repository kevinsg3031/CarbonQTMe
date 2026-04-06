#include "ProcessTracker.h"
#include "ContextSwitchAnalyzer.h"
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <cctype>

using namespace std;

static long getVmRSS(const std::string& pid) {
    ifstream file("/proc/" + pid + "/status");
    string line;
    while (std::getline(file, line)) {
        if (line.rfind("VmRSS:", 0) == 0) {
            try {
                return std::stol(line.substr(6));
            } catch (...) {
                return 0;
            }
        }
    }
    return 0;
}


static int getThreads(const std::string& pid) {
    ifstream file("/proc/" + pid + "/status");
    string line;
    while (std::getline(file, line)) {
        if (line.rfind("Threads:", 0) == 0) {
            try {
                return std::stoi(line.substr(8));
            } catch (...) {
                return 0;
            }
        }
    }
    return 0;
}


void ProcessTracker::printAllProcesses() {
    DIR* dir = opendir("/proc");
    dirent* entry;

    while ((entry = readdir(dir)) != nullptr) {
        if (!isdigit(entry->d_name[0])) continue;
        string pid = entry->d_name;
        ifstream comm("/proc/" + pid + "/comm");
        string name;
        getline(comm, name);

        long vcs, nvcs;
        ContextSwitchAnalyzer::getContextSwitches(pid, vcs, nvcs);

        double memMB = getVmRSS(pid) / 1024.0;
        int threads = getThreads(pid);

        std::cout << "PID: " << pid
                  << " | Name: " << name
                  << " | CPU: 0%"
                  << " | Memory: " << memMB << " MB"
                  << " | Threads: " << threads
                  << " | Voluntary CS: " << vcs
                  << " | Non-voluntary CS: " << nvcs
                  << "\n";
    }
    closedir(dir);
}

std::vector<ProcessRecord> ProcessTracker::collectProcesses() {
    std::vector<ProcessRecord> result;

    DIR* dir = opendir("/proc");
    dirent* entry;

    while ((entry = readdir(dir)) != nullptr) {
        if (!isdigit(entry->d_name[0])) continue;

        std::string pidStr = entry->d_name;
        int pid = std::stoi(pidStr);

        std::ifstream comm("/proc/" + pidStr + "/comm");
        std::string name;
        getline(comm, name);

        long vcs, nvcs;
        ContextSwitchAnalyzer::getContextSwitches(pidStr, vcs, nvcs);

        double memMB = getVmRSS(pidStr) / 1024.0;
        int threads = getThreads(pidStr);

        double cpu_percent = 0.0;

        double cpu_watts = 0.5 + cpu_percent * 0.02;
        double ram_watts = 0.3 + memMB * 0.0001;
        double total_watts = cpu_watts + ram_watts;

        double energy_joules = total_watts * 1.0; 
        double co2 = (energy_joules / 3'600'000.0) * 0.7;

        ProcessRecord rec;
        rec.pid = pid;
        rec.name = name;
        rec.cpu_percent = cpu_percent;
        rec.mem_mb = memMB;
        rec.threads = threads;
        rec.voluntary_cs = vcs;
        rec.nonvoluntary_cs = nvcs;
        rec.cpu_watts = cpu_watts;
        rec.ram_watts = ram_watts;
        rec.energy_joules = energy_joules;
        rec.co2e_kg = co2;

        result.push_back(rec);
    }

    closedir(dir);
    return result;
}
