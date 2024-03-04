#ifndef VALVEIDLISTMODEL_H
#define VALVEIDLISTMODEL_H

#include <QObject>
#include "ValveID.h"
#include <QList>
#include <QAbstractListModel>

using ValveIDList = QList<ValveID>;

class ValveIDListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ValveIDRoles
    {
        IDRole = Qt::UserRole + 1,
        ValueRole
    };

    Q_ENUM(ValveIDRoles);

    explicit ValveIDListModel(const ValveIDList &ids,QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    const ValveIDList &m_ids;
};

#endif // VALVEIDLISTMODEL_H
