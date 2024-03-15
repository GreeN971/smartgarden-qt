#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H
#include <memory>
#include <functional>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <QJsonDocument>

enum class httpVerb
{
    GET,
    POST
};

struct Header
{
    std::string name;
    std::string value;
};

struct HTTPClientRequest
{
    std::string uri;
    httpVerb reqType;
    std::optional<std::vector<uint8_t>> data;
    std::optional<std::vector<Header>> headers;
};

struct HTTPClientResponse
{
    std::string message;
    std::vector<uint8_t> data;
    int status;
};

typedef void CURL;
struct curl_slist;

class HTTPClient
{
public:
   HTTPClient();
   HTTPClientResponse Send(const HTTPClientRequest &req);

private:
    std::unique_ptr<CURL, void(*)(CURL *)> Initialize();
    void SetReqType(CURL *curl, httpVerb verb);
    void SetUrl(CURL *curl, std::string_view url);
    static size_t read_callback(char* buffer, size_t size, size_t nitems, void* userdata);
    static size_t write_callback(char* data, size_t elem_size, size_t elem_count, void* userptr);
    curl_slist *SetHeaders(CURL *curl, const std::vector<Header> &headers);
    void SetData(CURL* req, const std::vector<uint8_t> &data);

private:
    std::vector<uint8_t> m_requestData;
    size_t m_curReqOffset;
};

#endif // HTTPCLIENT_H
