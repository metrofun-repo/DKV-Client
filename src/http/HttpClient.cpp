#include "HttpClient.h"
#include "HttpResponse.h"
#include "third-party/httplib.h"

HttpClient::HttpClient(const std::string& host, int port, int connTimeout, int readTimeout, int writeTimeout)
    : host(host)
    , port(port)
    , connectionTimeoutMs(connTimeout)
    , readTimeoutMs(readTimeout)
    , writeTimeoutMs(writeTimeout)
{}

httplib::Client HttpClient::getConfiguredClient() const
{
    httplib::Client client(host, port);
    client.set_connection_timeout(connectionTimeoutMs / 1000, (connectionTimeoutMs % 1000) * 1000);
    client.set_read_timeout(readTimeoutMs / 1000, (readTimeoutMs % 1000) * 1000);
    client.set_write_timeout(writeTimeoutMs / 1000, (writeTimeoutMs % 1000) * 1000);
    return client;
}

HttpResponse HttpClient::post(const std::string& endpoint, const std::string& body)
{
    return makeResponse("POST", getConfiguredClient().Post(endpoint.c_str(), body, "text/plain"));
}

HttpResponse HttpClient::get(const std::string& endpoint) const
{
    return makeResponse("GET", getConfiguredClient().Get(endpoint.c_str()));
}

HttpResponse HttpClient::del(const std::string& endpoint)
{
    return makeResponse("DELETE", getConfiguredClient().Delete(endpoint.c_str()));
}
