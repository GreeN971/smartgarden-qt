#include "provider.h"
#include "httpclient.h"
#include <cstring>

Provider::Provider(std::string address) :
    m_address{address}
{
    HTTPClient client;
    HTTPClientRequest req;
    req.uri = m_address;
    req.reqType = httpVerb::GET;
    auto resp = client.Send(req);
    m_data = QString::fromLocal8Bit(QByteArrayView(resp.data.data(),resp.data.size()));

}

QString &Provider::GetData()
{
    return m_data;
}
