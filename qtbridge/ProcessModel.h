#pragma once

#include <QAbstractListModel>
#include <QModelIndex>
#include <QVariant>
#include <QHash>
#include <QString>
#include <QObject>

#include <vector>

#include "ProcessTracker.h"
#include "DataLogger.h"

class ProcessModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVariantList pidValues READ pidValues NOTIFY modelChanged)
    Q_PROPERTY(QVariantList threadValues READ threadValues NOTIFY modelChanged)
    Q_PROPERTY(QVariantList processNames READ processNames NOTIFY modelChanged)
    Q_PROPERTY(int totalThreads READ totalThreads NOTIFY modelChanged)

public:
    enum Roles
    {
        PidRole = Qt::UserRole + 1,
        NameRole,
        CpuRole,
        MemRole,
        ThreadsRole
    };

    explicit ProcessModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int totalThreads() const;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    QVariantList pidValues() const;
    QVariantList threadValues() const;
    QVariantList processNames() const;

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void setFilter(const QString &text);

signals:
    void modelChanged();

private:
    std::vector<ProcessRecord> m_allProcesses;
    std::vector<ProcessRecord> m_filteredProcesses;
    QString m_filter;
};
