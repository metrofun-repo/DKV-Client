#pragma once

#include "config/AppConfig.h"
#include "http/HttpClient.h"
#include "api/KeyValueApi.h"
#include "cli/CLIHandler.h"

class App
{
    AppConfig cfg;
    HttpClient httpClient;
    KeyValueApi keyValueApi;
    CLIHandler cliHandler;
public:
    App(AppConfig config);
    void run();
};