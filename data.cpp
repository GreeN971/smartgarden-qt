#include "data.h"
#include "worker.h"

Data::Data(QObject *parent)
    : QObject{parent}
    , m_tempeture(0)
    , m_airHumidity(0)
    , m_model(new SoilIDListModel(m_soilData, this))
{
    //Worker *worker = new Worker();
    //worker->moveToThread(&workerThread);
    //connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    //connect(this, )
}

Data &Data::operator=(const Data &data)
{
    m_tempeture = data.m_tempeture;
    m_airHumidity = data.m_airHumidity;
    m_soilData = data.m_soilData;
    m_filteredJson = data.m_filteredJson;
    m_errList = data.m_errList;
    return *this;
}

void Data::SetTempeture(int tempeture)
{
    m_tempeture = tempeture;
    emit tempetureChanged();
}

void Data::SetAirHumidity(int humi)
{
    m_airHumidity = humi;
    emit AirHumidityChanged();
}

void Data::SetSoilMoistures()
{
    m_soilData.clear();
    for(QJsonObject::const_iterator i = m_filteredJson.begin();  i != m_filteredJson.end(); ++i)
    {
        if(i.key().contains("soilMoisture"))
        {
            SoilID id;
            id.id = i.key();
            id.value = i.value().toInt();
            m_soilData.emplace_back(id);
        }
    }
    emit soilMoisturesChanged();
}

bool Data::ValidateJsonObjects()
{
    std::vector<QString> expectedJsonObjects = {"tempeture", "airhumidity",
                                                "soilMoistureOne", "soilMoistureTwo"};
    size_t len = sizeof(expectedJsonObjects) / sizeof(QString);

    for(QJsonObject::const_iterator i = m_filteredJson.begin(); i < m_filteredJson.end(); ++i)
    {
        for(size_t j = 0; j < len; j++)
        {
            if(i.key().isEmpty())
            {
                m_errList.name = i.key().toStdString();
                m_errList.status = "offline";
            }
            else if(!i.key().contains(expectedJsonObjects[j]))
            {
                qDebug() << "Object has typo or does not exists";
                continue;
            }
        }
    }

    return true; //TODO
}

void Data::FromJson(QJsonObject json)
{
    m_filteredJson = json;
    m_model->layoutAboutToBeChanged();
    //idealne asi nez ty data rozeslu tak pridat ten check zda jsou validni
    SetTempeture(m_filteredJson.value("tempeture").toInt());

    SetAirHumidity(m_filteredJson.value("airhumidity").toInt());

    SetSoilMoistures();

    for(const auto &soil : m_soilData)
        qDebug() << soil.id << soil.value;

    m_model->layoutChanged();
}

Data::~Data()
{
}





