#pragma once

#include <string>
#include <optional>

class HttpClient;
struct HttpResponse;

class KeyValueApi
{
    HttpClient& client;

    bool validateKey(const std::string& key, const char* func) const;
    bool validateValue(const std::string& value, const char* func) const;
    void handleError(const HttpResponse& response, const char* func) const;
    std::optional<std::string> handleErrorAndReturnEmpty(const HttpResponse& response, const char* func) const;

    std::string makeURL(const std::string& endpoint, const std::string& key) const;

public:
    KeyValueApi(HttpClient& cl);

    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    void remove(const std::string& key);
};