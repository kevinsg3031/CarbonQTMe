#include "EnergyEstimator.h"
#include "DataLogger.h"
#include <string>

static double getConfigDouble(DataLogger& logger, const std::string& key, double defaultValue) {
    std::string val = logger.getConfig(key);
    if (val.empty()) return defaultValue;
    try {
        return std::stod(val);
    } catch (...) {
        return defaultValue;
    }
}

EnergyMetrics EnergyEstimator::estimate(
    DataLogger& logger,    
    double cpu_percent,
    double ram_mb,
    double interval_seconds
) {
    double cpu_base = getConfigDouble(logger, "cpu_base_watts", 0.5);
    double cpu_factor = getConfigDouble(logger, "cpu_factor", 0.02);
    double ram_base = getConfigDouble(logger, "ram_base_watts", 0.3);
    double ram_factor = getConfigDouble(logger, "ram_factor", 0.0001);
    double carbon_intensity = getConfigDouble(logger, "carbon_intensity", 0.7);

    double cpu_watts = cpu_base + cpu_percent * cpu_factor;
    double ram_watts = ram_base + ram_mb * ram_factor;
    double total_watts = cpu_watts + ram_watts;

    double energy_joules = total_watts * interval_seconds;
    double kwh = energy_joules / 3'600'000.0;
    double co2 = kwh * carbon_intensity;

    return {cpu_watts, ram_watts, total_watts, energy_joules, co2};
}

