#pragma once

#include <string>

struct HttpResponse
{
    bool ok;
    bool networkError;
    int status;
    std::string body;
    std::string errorMsg;
};

namespace httplib { class Result; }

HttpResponse makeResponse(const std::string& httpMethod, const httplib::Result& result);