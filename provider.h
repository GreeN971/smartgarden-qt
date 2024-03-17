#ifndef PROVIDER_H
#define PROVIDER_H
#include <string>
#include <algorithm>
#include <QDebug>
#include <cstring>

class Provider
{
public:
    Provider(std::string address);
    QString &GetData();

private:


private:
    QString m_data;
    std::string m_address;
};

#endif // PROVIDER_H

/*    HTTPClient client;
    HTTPClientRequest req;
    req.uri = "http://192.168.11.28/espdata";
    req.reqType = httpVerb::GET;
    auto resp = client.Send(req);
    qDebug() << reinterpret_cast<const char*>(resp.data.data());
    qDebug() << resp.status; */
