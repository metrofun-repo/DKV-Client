#include "App.h"

App::App(AppConfig config)
    : cfg(config)
    , httpClient(cfg.host, cfg.port, cfg.connectionTimeoutMs, cfg.readTimeoutMs, cfg.writeTimeoutMs)
    , keyValueApi(httpClient)
    , cliHandler(httpClient, keyValueApi)
{}

void App::run()
{
    cliHandler.run();
}