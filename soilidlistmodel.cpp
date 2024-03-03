#include "soilidlistmodel.h"

SoilIDListModel::SoilIDListModel(const SoilIDList &ids, QObject *parent)
    : QAbstractListModel{parent}, m_ids{ids}
{

}

int SoilIDListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return m_ids.count();
}

QVariant SoilIDListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= m_ids.size())
        return QVariant();

    const SoilID &soilID = m_ids.at(index.row());
    if(role == IDRole)
        return soilID.id;
    else if(role == ValueRole)
        return soilID.value;
    else
        return QVariant();
}

QHash<int, QByteArray> SoilIDListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IDRole] = "soilID";
    roles[ValueRole] = "soilValue";

    return roles;
}
