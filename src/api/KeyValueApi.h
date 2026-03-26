#pragma once

#include <string>
#include <optional>

#include <nlohmann/json.hpp>

#include "core/types/BasicResult.h"
#include "http/HttpClient.h"
#include "http/HttpResponse.h"

class KeyValueApi
{
    using StorageKey       = std::string;
    using StorageValue     = std::string;

    using Json             = nlohmann::json;
    using ValidationResult = BasicResult<void>;
    using JsonResult       = BasicResult<Json>;
    using ApiCallResult    = BasicResult<std::optional<StorageValue>>;
    using JsonPrintResult  = BasicResult<void>;
    using JsonPrintResult  = BasicResult<void>;

    
public:
    KeyValueApi(HttpClient& cl);

    ApiCallResult set(const StorageKey& key, const StorageValue& value);
    ApiCallResult get(const StorageKey& key);
    ApiCallResult remove(const StorageKey& key);
private:
    std::string makeURL(const std::string& endpoint, const std::string& key) const;
    ValidationResult validateKey(const StorageKey& key, const char* func) const;
    ValidationResult validateValue(const StorageValue& value, const char* func) const;
    JsonResult parseJson(const HttpResponse& response, const char* func) const;

    void printJsonPayload(const Json& json, const char* func) const;

    HttpClient& client;
};