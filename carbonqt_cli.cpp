#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>
#include <algorithm>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "ProcessTracker.h"
#include "SystemMonitor.h"
#include "EnergyEstimator.h"

struct ProcessInfo {
    int pid;
    std::string name;
    int contextSwitches;
    double cpu;
    double memory;
    double carbon;
};

void printTable(const std::vector<ProcessInfo>& processes) {
    std::cout << std::left
              << std::setw(8) << "PID"
              << std::setw(20) << "Name"
              << std::setw(18) << "Ctx Switches"
              << std::setw(10) << "CPU%"
              << std::setw(10) << "Mem"
              << std::setw(12) << "Carbon\n";

    for (const auto& p : processes) {
        std::cout << std::setw(8) << p.pid
                  << std::setw(20) << p.name
                  << std::setw(18) << p.contextSwitches
                  << std::setw(10) << p.cpu
                  << std::setw(10) << p.memory
                  << std::setw(12) << p.carbon
                  << "\n";
    }
}

#include <thread>
#include <chrono>

void runCommand(int seconds) {
    std::cout << "Running for " << seconds << " seconds...\n";

    ProcessTracker tracker;

    for (int i = 0; i < seconds; i++) {

        auto processes = tracker.collectProcesses();
        std::vector<ProcessInfo> tableData;

        for (auto& p : processes) {
            ProcessInfo info;
            info.pid = p.pid;
            info.name = p.name;
            info.contextSwitches = p.voluntary_cs + p.nonvoluntary_cs;
            info.cpu = p.cpu_percent;
            info.memory = p.mem_mb;
            info.carbon = p.co2e_kg;

            tableData.push_back(info);
        }

        std::cout << "\n--- Second " << i+1 << " ---\n";
        printTable(tableData);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void statusCommand() {
    std::cout << "CarbonQt CLI running\n";
}

void topCommand() {
    ProcessTracker tracker;
    auto processes = tracker.collectProcesses();

    std::sort(processes.begin(), processes.end(),
              [](auto& a, auto& b) {
                  return a.co2e_kg > b.co2e_kg;
              });

    std::cout << "Top Carbon Processes:\n\n";

    std::cout << std::left
              << std::setw(8)  << "PID"
              << std::setw(25) << "Name"
              << std::setw(15) << "Memory(MB)"
              << std::setw(15) << "Carbon(kg)"
              << "\n";

    std::cout << std::string(65, '-') << "\n";

    int limit = std::min(10, (int)processes.size());

    for (int i = 0; i < limit; i++) {
        auto& p = processes[i];

        std::cout << std::setw(8)  << p.pid
                  << std::setw(25) << p.name
                  << std::setw(15) << p.mem_mb
                  << std::setw(15) << p.co2e_kg
                  << "\n";
    }
}

#include <thread>
#include <chrono>

void watchCommand() {
    ProcessTracker tracker;

    while (true) {
        system("clear");  // clears screen for live effect

        auto processes = tracker.collectProcesses();
        std::vector<ProcessInfo> tableData;

        for (auto& p : processes) {
            ProcessInfo info;
            info.pid = p.pid;
            info.name = p.name;
            info.contextSwitches = p.voluntary_cs + p.nonvoluntary_cs;
            info.cpu = p.cpu_percent;
            info.memory = p.mem_mb;
            info.carbon = p.co2e_kg;

            tableData.push_back(info);
        }

        std::cout << "CarbonQt Live Monitor (Press Ctrl+C to exit)\n\n";

        printTable(tableData);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void filterCommand(const std::string& name) {
    ProcessTracker tracker;
    auto processes = tracker.collectProcesses();

    std::cout << "Filtered processes: " << name << "\n\n";

    std::cout << std::left
              << std::setw(8)  << "PID"
              << std::setw(25) << "Name"
              << std::setw(15) << "Memory(MB)"
              << std::setw(15) << "Carbon(kg)"
              << "\n";

    std::cout << std::string(65, '-') << "\n";

    for (auto& p : processes) {
        if (p.name.find(name) != std::string::npos) {
            std::cout << std::setw(8)  << p.pid
                      << std::setw(25) << p.name
                      << std::setw(15) << p.mem_mb
                      << std::setw(15) << p.co2e_kg
                      << "\n";
        }
    }
}

void summaryCommand() {
    ProcessTracker tracker;
    auto processes = tracker.collectProcesses();

    int totalProcesses = processes.size();
    int totalThreads = 0;
    double totalCarbon = 0;

    for (auto& p : processes) {
        totalThreads += p.threads;
        totalCarbon += p.co2e_kg;
    }

    std::cout << "System Summary:\n\n";
    std::cout << "Processes: " << totalProcesses << "\n";
    std::cout << "Threads: " << totalThreads << "\n";
    std::cout << "Total Carbon: " << totalCarbon << " kg\n";
}

void guiCommand() {
    system("/usr/local/bin/appMyApp");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: carbonqt <gui|status|run|top|watch|filter|summary>\n";
        return 1;
    }

    std::string cmd = argv[1];

    if (cmd == "run") {
        if (argc < 3) {
            std::cerr << "Provide duration (seconds)\n";
            return 1;
        }
        int seconds = std::stoi(argv[2]);
        runCommand(seconds);
    }
    else if (cmd == "status") {
        statusCommand();
    }
    else if (cmd == "top") {
        topCommand();
    }
    else if (cmd == "watch") {
        watchCommand();
    }
    else if (cmd == "filter") {
        if (argc < 3) {
            std::cerr << "Provide process name\n";
            return 1;
        }
        filterCommand(argv[2]);
    }
    else if (cmd == "summary") {
        summaryCommand();
    }
    else if (cmd == "gui") {
        guiCommand();
    }
    else {
        std::cerr << "Unknown command\n";
    }

    return 0;
}
