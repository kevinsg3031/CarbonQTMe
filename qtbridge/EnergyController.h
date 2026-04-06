#pragma once

#include <QObject>
#include "EnergyEstimator.h"
#include "SystemMonitor.h"
#include "DataLogger.h"

class EnergyController : public QObject {
    Q_OBJECT

    Q_PROPERTY(double cpuWatts READ cpuWatts NOTIFY dataChanged)
    Q_PROPERTY(double ramWatts READ ramWatts NOTIFY dataChanged)
    Q_PROPERTY(double totalWatts READ totalWatts NOTIFY dataChanged)
    Q_PROPERTY(double energyJoules READ energyJoules NOTIFY dataChanged)
    Q_PROPERTY(double co2 READ co2 NOTIFY dataChanged)

public:
    explicit EnergyController(QObject *parent = nullptr);

    double cpuWatts() const;
    double ramWatts() const;
    double totalWatts() const;
    double energyJoules() const;
    double co2() const;

signals:
    void dataChanged();

private:
    DataLogger logger;
    EnergyMetrics metrics;
};
