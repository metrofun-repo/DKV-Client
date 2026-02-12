#pragma once

#include <string>

struct AppConfig
{
    std::string host = "127.0.0.1";
    int port = 8080;
    int connectionTimeoutMs = 3000;
    int readTimeoutMs = 3000;
    int writeTimeoutMs = 3000;
};