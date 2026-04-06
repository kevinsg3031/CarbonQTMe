#pragma once

#include <QObject>

class MonitorController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double cpuUsage READ cpuUsage NOTIFY dataChanged)
    Q_PROPERTY(int coreCount READ coreCount NOTIFY dataChanged)
    Q_PROPERTY(double memoryUsed READ memoryUsed NOTIFY dataChanged)
    Q_PROPERTY(double ramUsage READ ramUsage NOTIFY dataChanged)

public:
    explicit MonitorController(QObject *parent = nullptr);

    double cpuUsage() const;
    int coreCount() const;
    double memoryUsed() const;
    double ramUsage() const;

    Q_INVOKABLE void updateStats();

signals:
    void dataChanged();

private:
    double m_cpuUsage = 0;
    int m_coreCount = 0;
    double m_memoryUsed = 0;
    double m_ramUsage = 0;
};
