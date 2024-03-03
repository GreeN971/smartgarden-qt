#ifndef SOILIDLISTMODEL_H
#define SOILIDLISTMODEL_H

#include "SoilID.h"
#include <QObject>
#include <QAbstractListModel>
#include <QList>

using SoilIDList = QList<SoilID>;


class SoilIDListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum SoilIDRoles
    {
        IDRole = Qt::UserRole + 1,
        ValueRole
    };

    Q_ENUM(SoilIDRoles)
    explicit SoilIDListModel(const SoilIDList &ids, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;;
protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    const SoilIDList &m_ids;
};

#endif // SOILIDLISTMODEL_H
