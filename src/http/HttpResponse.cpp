#include "HttpResponse.h"
#include "third-party/httplib.h"

HttpResponse makeResponse(const std::string& httpMethod, const httplib::Result& result)
{
    HttpResponse resp;
    if(!result)
    {
        std::cout << httpMethod << " request Http error: " << httplib::to_string(result.error()) << std::endl;
        resp.networkError = true;
        resp.ok = false;
        resp.status = 0;
        resp.errorMsg = httplib::to_string(result.error());
        return resp;
    }
   
    std::cout  << httpMethod << " request Http status: " << result->status << " body: " << result->body << std::endl;
   
    resp.networkError = false;
    resp.status = result->status;
    resp.body = result->body;
    resp.ok = result->status >= httplib::OK_200 && result->status < httplib::MultipleChoices_300;
    
    return resp;
}