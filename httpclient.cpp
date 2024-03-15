#include "httpclient.h"
#include <curl/curl.h>

HTTPClient::HTTPClient()
{

}

std::unique_ptr<CURL, void(*)(CURL *)> HTTPClient::Initialize()
{
    std::unique_ptr<CURL, void(*)(CURL*)> curl(curl_easy_init(), curl_easy_cleanup);

    if (!curl.get())
        throw std::runtime_error("Failed to allocate memory for httpClient");

    CURLcode status = curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, &write_callback);
    if (status != CURLE_OK)
        throw std::runtime_error("Setting write function failed");


    return curl;
}

void HTTPClient::SetReqType(CURL *curl, httpVerb verb)
{
    static CURLoption reqTypeOpts[] {
        CURLoption::CURLOPT_HTTPGET,
        CURLoption::CURLOPT_POST //maybe use HTTPGET, but that is for later
    };

    CURLcode status = CURLE_OK;

    status = curl_easy_setopt(curl, reqTypeOpts[(int)verb], true);
    if (status != CURLE_OK )
        throw std::runtime_error("Setting req type failed");
}

void HTTPClient::SetUrl(CURL *curl, std::string_view url)
{
    CURLcode status = curl_easy_setopt(curl, CURLoption::CURLOPT_URL, url.data());
    if(status != CURLE_OK)
        throw std::runtime_error("Setting URL failed");
}

size_t HTTPClient::read_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
    HTTPClient *client = static_cast<HTTPClient*>(userdata);
    size_t toSend = std::min(size * nitems, client->m_requestData.size() - client->m_curReqOffset);//if eqv returns A.
    std::memcpy(buffer, client->m_requestData.data() + client->m_curReqOffset, toSend);
    client->m_curReqOffset += toSend;

    return toSend;
}

size_t HTTPClient::write_callback(char *data, size_t elem_size, size_t elem_count, void *userptr)
{
    std::basic_ostringstream<uint8_t> *output = reinterpret_cast<std::basic_ostringstream<uint8_t>*>(userptr);
    output->write(reinterpret_cast<uint8_t*>(data), elem_size * elem_count);
    return elem_size * elem_count;
}

std::string AssembleHeader(const Header &header)
{
    return header.name + ": " + header.value;
}

curl_slist *HTTPClient::SetHeaders(CURL *curl, const std::vector<Header> &headers)
{
    curl_slist *headerList = nullptr;
    for(size_t i = 0; i < headers.size(); i++)
        headerList = curl_slist_append(headerList, AssembleHeader(headers.at(i)).c_str());

    CURLcode status = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);
    if(status != CURLE_OK)
        throw std::runtime_error("Setting headers failed");

    return headerList;
}

void HTTPClient::SetData(CURL *req, const std::vector<uint8_t> &data)
{
    CURLcode status = curl_easy_setopt(req, CURLOPT_INFILESIZE_LARGE, static_cast<curl_off_t>(data.size()));
    if(status != CURLE_OK)
        throw std::runtime_error("Setting sent data size failed");

    m_curReqOffset = 0;
    m_requestData = data;

    status = curl_easy_setopt(req, CURLOPT_READDATA, this);
    if(status != CURLE_OK)
    {
        m_requestData.clear();
        throw std::runtime_error("Setting post data failed");
    }
    status = curl_easy_setopt(req, CURLOPT_READFUNCTION, read_callback);
    if(status != CURLE_OK)
    {
        m_requestData.clear();
        throw std::runtime_error("Setting post data failed");
    }
}

HTTPClientResponse HTTPClient::Send(const HTTPClientRequest &req)
{
    HTTPClientResponse resp;

    std::unique_ptr<CURL, void(*)(CURL *)> curl(Initialize());
    if(!curl.get())
        throw std::runtime_error("Failed to allocated memory for HTTP client");

    SetReqType(curl.get(), req.reqType);
    SetUrl(curl.get(), req.uri);
    if(req.data.has_value())
        SetData(curl.get(), req.data.value());

    std::unique_ptr<curl_slist, void(*)(curl_slist*)> headers(nullptr, &curl_slist_free_all);
    if(req.headers.has_value())
        headers.reset(SetHeaders(curl.get(), req.headers.value()));

    std::basic_ostringstream<uint8_t> resultStream;
    CURLcode status = curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &resultStream);
    if(status != CURLE_OK)
        throw std::runtime_error("Setting write function data failed");

    status = curl_easy_perform(curl.get());

    curl_easy_getinfo(curl.get(), CURLINFO_HTTP_CODE, &resp.status);
    if(status != CURLE_OK)
        throw std::runtime_error("Send req failed " + std::to_string(resp.status));

    auto data = resultStream.str();
    resp.data = std::vector<uint8_t>(data.c_str(), data.c_str() + data.size());

    return resp;
}











