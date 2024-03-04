#include "valveidlistmodel.h"

ValveIDListModel::ValveIDListModel(const ValveIDList &ids, QObject *parent)
    : QAbstractListModel{parent}, m_ids{ids}
{

}

int ValveIDListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return m_ids.count();
}

QVariant ValveIDListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= m_ids.size())
        return QVariant();

    const ValveID &valveID = m_ids.at(index.row());
    if(role == IDRole)
        return valveID.id;
    else if(role == ValueRole)
        return valveID.value;
    else
        return QVariant();
}

QHash<int, QByteArray> ValveIDListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[IDRole] = "valveID";
    roles[ValueRole] = "valveValue";

    return roles;
}
