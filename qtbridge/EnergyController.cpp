#include "EnergyController.h"
#include <QTimer>
#include <numeric>

EnergyController::EnergyController(QObject *parent)
    : QObject(parent),
      logger("carbonqt.db")
{
    logger.init();

    auto timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this]() {
        // 1️⃣ Get system usage
        auto cores = SystemMonitor::getCpuUsagePerCore();
        double cpuPercent = cores.empty()
            ? 0.0
            : std::accumulate(cores.begin(), cores.end(), 0.0) / cores.size();

        double ramUsedMB, swap;
        SystemMonitor::getMemoryUsage(ramUsedMB, swap);

        metrics = EnergyEstimator::estimate(
            logger,
            cpuPercent,
            ramUsedMB,
            1.0
        );

        emit dataChanged();
    });

    timer->start(1000);
}

double EnergyController::cpuWatts() const {
    return metrics.cpu_watts;
}

double EnergyController::ramWatts() const {
    return metrics.ram_watts;
}

double EnergyController::totalWatts() const {
    return metrics.total_watts;
}

double EnergyController::energyJoules() const {
    return metrics.energy_joules;
}

double EnergyController::co2() const {
    return metrics.co2e_kg;
}
