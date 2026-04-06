#pragma once
#include "DataLogger.h"

struct EnergyMetrics {
    double cpu_watts;
    double ram_watts;
    double total_watts;
    double energy_joules;
    double co2e_kg;
};

class EnergyEstimator {
public:
    static EnergyMetrics estimate(
        DataLogger& logger,  
        double cpu_percent,
        double ram_mb,
        double interval_seconds
    );
};

