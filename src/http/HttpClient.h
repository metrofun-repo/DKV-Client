#pragma once

#include <string>

struct HttpResponse;

namespace httplib { class Client; }

class HttpClient
{
    std::string host;
    int port;

    int connectionTimeoutMs;
    int readTimeoutMs;
    int writeTimeoutMs;

    httplib::Client getConfiguredClient() const;

public:
    HttpClient(const std::string& host, int port, int connTimeout, int readTimout, int writeTimeout);

    HttpResponse post(const std::string& endpoint, const std::string& body);
    HttpResponse get(const std::string& endpoint) const;
    HttpResponse del(const std::string& endpoint);

    inline std::string getHost() const { return host; }
    inline int getPort() const { return port; }

    inline void setConnectionTimeout(int timeout) { connectionTimeoutMs = timeout; }
    inline void setReadTimeout(int timeout) { readTimeoutMs = timeout; }
    inline void setWriteTimeout(int timeout) { writeTimeoutMs = timeout; }

    inline int getConnectionTimeout() const { return connectionTimeoutMs; }
    inline int getReadTimeout() const { return readTimeoutMs; }
    inline int getWriteTimeout() const { return writeTimeoutMs; }

};