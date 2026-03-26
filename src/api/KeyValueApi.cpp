#include "KeyValueApi.h"

#include <iostream>

#include "Endpoints.h"

#include "http/HttpConstants.h"

KeyValueApi::KeyValueApi(HttpClient& cl)
    : client(cl)
{}

std::string KeyValueApi::makeURL(const std::string& endpoint, const std::string& key) const
{
    return endpoint + '?' + Http::Param::KEY + '=' + key;
}

KeyValueApi::ValidationResult KeyValueApi::validateKey(const std::string& key, const char* func) const
{
    if(key.empty())
    {
        return ValidationResult::makeFailure(std::string(func) + " Invalid argument: key cannot be empty");
    }
    return ValidationResult::makeSuccess();
}

KeyValueApi::ValidationResult KeyValueApi::validateValue(const std::string& value, const char* func) const
{
    if(value.empty())
    {
        return ValidationResult::makeFailure(std::string(func) + " Invalid argument: value cannot be empty");
    }
    return ValidationResult::makeSuccess();
}

KeyValueApi::JsonResult KeyValueApi::parseJson(const HttpResponse& response, const char* func) const
{
    auto jsonResponse = nlohmann::json::parse(response.body, nullptr, false);
    if(jsonResponse.is_discarded())
    {
        return JsonResult::makeFailure(std::string(func) + " Failed to parse response JSON");
    }
    return JsonResult::makeSuccess(std::move(jsonResponse));
}

void KeyValueApi::printJsonPayload(const Json& json, const char* func) const
{
    // bool success = json["success"].get<bool>();
    // auto status  = json["status"].get<std::string>();
    // auto message = json["message"].get<std::string>();
    // Json data;
    // if(json.contains("data"))
    // {
    //     data = json["data"];
    // }
    // std::cout << func <<" response: "
    //           << "\n\tsuccess = " << success 
    //           << "\n\t status = " << status 
    //           << "\n\tmessage = " << message
    //           << "\n\t   data = " << data.dump(4)
    //           << std::endl; 
    std::cout << func <<" response: \n" << json.dump(4);
}

KeyValueApi::ApiCallResult KeyValueApi::set(const std::string& key, const std::string& value)
{
    auto valid = validateKey(key, __func__);
    if(!valid.hasValue())
    {
        return ApiCallResult::makeFailure(std::string(__func__) + " Validation failed: " + valid.error().details);
    }
    valid = validateValue(value, __func__);
    if(!valid.hasValue())
    {
        return ApiCallResult::makeFailure(std::string(__func__) + " Validation failed: " + valid.error().details);
    }

    nlohmann::json json = {
        { "value", value }
    };

    auto response = client.post(makeURL(Endpoints::PUBLIC, key), json.dump());

    if(!response.ok)
    {
        return ApiCallResult::makeFailure(std::string(__func__) + " Error occurred: " + std::string(response.errorMsg));
    }

    auto jsonParse = parseJson(response, __func__);
    if(!jsonParse.hasValue())
    {
        return ApiCallResult::makeFailure(std::string(__func__) + " Error occurred: " + jsonParse.error().details);
    }

    std::cout << __func__ <<" response: \n" << jsonParse.value().dump(4);

    return ApiCallResult::makeSuccess(std::nullopt);
}

KeyValueApi::ApiCallResult KeyValueApi::get(const std::string& key)
{
    auto valid = validateKey(key, __func__);
    if(!valid.hasValue())
    {
        return ApiCallResult::makeFailure(std::string(__func__) + " Validation failed: " + valid.error().details);
    }
    auto response = client.get(makeURL(Endpoints::PUBLIC, key));

    if(!response.ok)
    {
        return ApiCallResult::makeFailure(std::string(__func__) + " Error occurred: " + response.errorMsg);
    }

    auto jsonParse = parseJson(response, __func__);
    if(!jsonParse.hasValue())
    {
        return ApiCallResult::makeFailure(std::string(__func__) + " Error occurred: " + jsonParse.error().details);
    }

    std::cout << __func__ <<" response: \n" << jsonParse.value().dump(4);

    const auto & jsonPayload = jsonParse.value();

    if(!jsonPayload.contains("data"))
    {
        return ApiCallResult::makeFailure(std::string(__func__) + " Error occurred: Invalid response JSON");
    }

    const auto& jsonData = jsonPayload["data"];

    if(!jsonData.contains("value"))
    {
        return ApiCallResult::makeFailure(std::string(__func__) + " Error occurred: Invalid response JSON");
    }

    const auto& jsonValue = jsonData["value"].get<StorageValue>();

    return ApiCallResult::makeSuccess(jsonValue);
}

KeyValueApi::ApiCallResult KeyValueApi::remove(const std::string& key)
{
    auto valid = validateKey(key, __func__);
    if(!valid.hasValue())
    {
        return ApiCallResult::makeFailure(std::string(__func__) + " Validation failed: " + valid.error().details);
    }

    auto response = client.del(makeURL(Endpoints::PUBLIC, key));
    
    if(!response.ok)
    {
        return ApiCallResult::makeFailure(std::string(__func__) + " Error occurred: " + std::string(response.errorMsg));
    }

    auto jsonParse = parseJson(response, __func__);
    if(!jsonParse.hasValue())
    {
        return ApiCallResult::makeFailure(std::string(__func__) + " Error occurred: " + jsonParse.error().details);
    }

    std::cout << __func__ <<" response: \n" << jsonParse.value().dump(4) << std::endl;

    return ApiCallResult::makeSuccess(std::nullopt);
}