#ifndef SOILID_H
#define SOILID_H
#include <QString>
#include <QMetaType>

struct SoilID
{
    QString id; //fix so it is not std::string
    int value;
};


#endif // SOILID_H
