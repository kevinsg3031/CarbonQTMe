#pragma once
#include <string>
#include <vector>
#include <sqlite3.h>

struct ProcessRecord {
    int pid;
    std::string name;
    double cpu_percent;
    double mem_mb;
    int threads;
    int voluntary_cs;
    int nonvoluntary_cs;
    double cpu_watts;
    double ram_watts;
    double energy_joules;
    double co2e_kg;
};

class DataLogger {
public:
    DataLogger(const std::string& dbPath);
    ~DataLogger();

    void init();

    void logSystem(double cpu, double mem, double gpu,
                   double cpu_watts, double gpu_watts, double ram_watts,
                   double energy, double co2);

    void logProcesses(const std::vector<ProcessRecord>& processes);

    void setConfig(const std::string& key, const std::string& value);
    std::string getConfig(const std::string& key);

private:
    sqlite3* db;
};

