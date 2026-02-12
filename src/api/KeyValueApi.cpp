#include "KeyValueApi.h"

#include <iostream>

#include "Endpoints.h"

#include "http/HttpClient.h"
#include "http/HttpResponse.h"
#include "http/HttpConstants.h"

KeyValueApi::KeyValueApi(HttpClient& cl)
    : client(cl)
{
}

bool KeyValueApi::validateKey(const std::string& key, const char* func) const
{
    if(key.empty())
    {
        std::cout << func << " Invalid argument: key cannot be empty" << std::endl;
        return false;
    }
    return true;
}

bool KeyValueApi::validateValue(const std::string& value, const char* func) const
{
    if(value.empty())
    {
        std::cout << func <<  " Invalid argument: value cannot be empty" << std::endl;
        return false;
    }
    return true;
}

void KeyValueApi::handleError(const HttpResponse& response, const char* func) const
{
    if(!response.ok)
    {
        std::cout << func << " Error occurred: " << response.errorMsg << std::endl;
    }
}

std::optional<std::string> KeyValueApi::handleErrorAndReturnEmpty(const HttpResponse& response, const char* func) const
{
    handleError(response, func);
    return std::nullopt;
}

std::string KeyValueApi::makeURL(const std::string& endpoint, const std::string& key) const
{
    return endpoint + '?' + Http::Param::KEY + '=' + key;
}


void KeyValueApi::set(const std::string& key, const std::string& value)
{
    if(!validateKey(key, __func__) || !validateValue(value, __func__)) return;

    auto response = client.post(makeURL(Endpoints::SET, key), value);

    handleError(response, __func__);
}

std::optional<std::string> KeyValueApi::get(const std::string& key)
{
    if(!validateKey(key, __func__)) return std::nullopt;
    
    auto response = client.get(makeURL(Endpoints::GET, key));

    return response.ok ? response.body : handleErrorAndReturnEmpty(response, __func__);
}

void KeyValueApi::remove(const std::string& key)
{
    if(!validateKey(key, __func__)) return;

    auto response = client.del(makeURL(Endpoints::REMOVE, key));
    
    handleError(response, __func__);
}