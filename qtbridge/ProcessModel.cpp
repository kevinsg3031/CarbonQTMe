#include "ProcessModel.h"
#include <algorithm>

ProcessModel::ProcessModel(QObject *parent)
    : QAbstractListModel(parent)
{
    refresh();
}

int ProcessModel::rowCount(const QModelIndex &) const
{
    return static_cast<int>(m_filteredProcesses.size());
}

QVariant ProcessModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() ||
        index.row() < 0 ||
        index.row() >= (int)m_filteredProcesses.size())
        return {};

    const auto &p = m_filteredProcesses[index.row()];

    switch (role) {
    case PidRole: return p.pid;
    case NameRole: return QString::fromStdString(p.name);
    case CpuRole: return p.cpu_percent;
    case MemRole: return p.mem_mb;
    case ThreadsRole: return p.threads;
    }

    return {};
}

QHash<int, QByteArray> ProcessModel::roleNames() const
{
    return {
        {PidRole, "pid"},
        {NameRole, "name"},
        {CpuRole, "cpu"},
        {MemRole, "memory"},
        {ThreadsRole, "threads"}
    };
}

void ProcessModel::refresh()
{
    beginResetModel();

    m_allProcesses = ProcessTracker::collectProcesses();
    m_filteredProcesses.clear();

    for (const auto &p : m_allProcesses)
    {
        if (p.threads <= 5)
            continue;

        QString name = QString::fromStdString(p.name);

        if (m_filter.isEmpty() ||
            name.contains(m_filter, Qt::CaseInsensitive))
        {
            m_filteredProcesses.push_back(p);
        }
    }

    std::sort(m_filteredProcesses.begin(),
              m_filteredProcesses.end(),
              [](const ProcessRecord &a, const ProcessRecord &b)
              {
                  return a.pid < b.pid;
              });

    endResetModel();
    emit modelChanged();
}

void ProcessModel::setFilter(const QString &text)
{
    m_filter = text;
    refresh();
}

QVariantList ProcessModel::pidValues() const
{
    QVariantList list;
    for (const auto &p : m_filteredProcesses)
        list.append(p.pid);
    return list;
}

QVariantList ProcessModel::threadValues() const
{
    QVariantList list;
    for (const auto &p : m_filteredProcesses)
        list.append(p.threads);
    return list;
}

QVariantList ProcessModel::processNames() const
{
    QVariantList list;
    for (const auto &p : m_filteredProcesses)
        list.append(QString::fromStdString(p.name));
    return list;
}

int ProcessModel::totalThreads() const
{
    int total = 0;

    for (const auto &p : m_filteredProcesses)
        total += p.threads;

    return total;
}
