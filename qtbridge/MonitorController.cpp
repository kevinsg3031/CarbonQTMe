#include "MonitorController.h"
#include "SystemMonitor.h"
#include <QTimer>
#include <numeric>

MonitorController::MonitorController(QObject *parent)
    : QObject(parent)
{
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        emit dataChanged();
    });
    timer->start(1000);
}

double MonitorController::cpuUsage() const {
    auto cores = SystemMonitor::getCpuUsagePerCore();
    if (cores.empty()) return 0.0;

    double sum = std::accumulate(cores.begin(), cores.end(), 0.0);
    return sum / cores.size();
}

int MonitorController::coreCount() const {
    return (int)SystemMonitor::getCpuUsagePerCore().size();
}

double MonitorController::memoryUsed() const {
    double used, swap;
    SystemMonitor::getMemoryUsage(used, swap);
    return used;
}

double MonitorController::ramUsage() const
{
    return m_ramUsage;
}

void MonitorController::updateStats()
{
    m_ramUsage = SystemMonitor::getRamUsage();
    emit dataChanged();
}
