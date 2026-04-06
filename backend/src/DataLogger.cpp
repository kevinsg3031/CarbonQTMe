#include "DataLogger.h"
#include <iostream>
#include <ctime>

DataLogger::DataLogger(const std::string& path) {
    sqlite3_open(path.c_str(), &db);
}

DataLogger::~DataLogger() {
    sqlite3_close(db);
}

void DataLogger::init() {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS system_metrics (
            timestamp INTEGER,
            cpu_percent REAL,
            mem_mb REAL,
            gpu_percent REAL,
            cpu_watts REAL,
            gpu_watts REAL,
            ram_watts REAL,
            energy_joules REAL,
            co2e_kg REAL
        );

        CREATE TABLE IF NOT EXISTS process_metrics (
            timestamp INTEGER,
            pid INTEGER,
            name TEXT,
            cpu_percent REAL,
            mem_mb REAL,
            threads INTEGER,
            voluntary_cs INTEGER,
            nonvoluntary_cs INTEGER,
            cpu_watts REAL,
            ram_watts REAL,
            energy_joules REAL,
            co2e_kg REAL
        );

        CREATE TABLE IF NOT EXISTS config (
            key TEXT PRIMARY KEY,
            value TEXT NOT NULL
        );
    )";

    sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
}

void DataLogger::logSystem(double cpu, double mem, double gpu,
                           double cpu_watts, double gpu_watts, double ram_watts,
                           double energy, double co2) {

    std::string sql =
        "INSERT INTO system_metrics VALUES (" +
        std::to_string(time(nullptr)) + "," +
        std::to_string(cpu) + "," +
        std::to_string(mem) + "," +
        std::to_string(gpu) + "," +
        std::to_string(cpu_watts) + "," +
        std::to_string(gpu_watts) + "," +
        std::to_string(ram_watts) + "," +
        std::to_string(energy) + "," +
        std::to_string(co2) + ");";

    sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
}

void DataLogger::logProcesses(const std::vector<ProcessRecord>& processes) {
    int ts = time(nullptr);

    sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

    for (const auto& p : processes) {
        std::string sql =
            "INSERT INTO process_metrics VALUES (" +
            std::to_string(ts) + "," +
            std::to_string(p.pid) + ",'" +
            p.name + "'," +
            std::to_string(p.cpu_percent) + "," +
            std::to_string(p.mem_mb) + "," +
            std::to_string(p.threads) + "," +
            std::to_string(p.voluntary_cs) + "," +
            std::to_string(p.nonvoluntary_cs) + "," +
            std::to_string(p.cpu_watts) + "," +
            std::to_string(p.ram_watts) + "," +
            std::to_string(p.energy_joules) + "," +
            std::to_string(p.co2e_kg) + ");";

        sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    }

    sqlite3_exec(db, "COMMIT;", nullptr, nullptr, nullptr);
}

void DataLogger::setConfig(const std::string& key, const std::string& value) {
    std::string sql =
        "INSERT OR REPLACE INTO config VALUES ('" + key + "','" + value + "');";
    sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
}

std::string DataLogger::getConfig(const std::string& key) {
    std::string result;
    std::string sql = "SELECT value FROM config WHERE key='" + key + "';";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = (const char*)sqlite3_column_text(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return result;
}

