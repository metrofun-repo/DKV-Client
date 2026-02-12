#include "CLIHandler.h"

#include <iostream>
#include <sstream>

#include "http/HttpClient.h"
#include "api/KeyValueApi.h"

CLIHandler::CLIHandler(HttpClient& client, KeyValueApi& api)
    : running(false)
    , httpClient(client)
    , keyValueApi(api)
{
    commands = 
    {
        { "set"               , [&](const std::vector<std::string>& args) { cmdSet(args); } },
        { "get"               , [&](const std::vector<std::string>& args) { cmdGet(args); } },
        { "remove"            , [&](const std::vector<std::string>& args) { cmdRemove(args); } },
        { "set-conn-timeout"  , [&](const std::vector<std::string>& args) { setTimeout(args, "set-conn-timeout" , [&](int timeout) { httpClient.setConnectionTimeout(timeout); }); } },
        { "set-read-timeout"  , [&](const std::vector<std::string>& args) { setTimeout(args, "set-read-timeout" , [&](int timeout) { httpClient.setReadTimeout(timeout); }); } },
        { "set-write-timeout" , [&](const std::vector<std::string>& args) { setTimeout(args, "set-write-timeout", [&](int timeout) { httpClient.setWriteTimeout(timeout); }); } },
        { "show-config"       , [&](const std::vector<std::string>&) { cmdShowConfig(); } },
        { "help"              , [&](const std::vector<std::string>&) { cmdHelp(); } },
        { "exit"              , [&](const std::vector<std::string>&) { cmdExit(); } }
    };
}

void CLIHandler::printInvalidArgs(const char* cmd) const
{
    std::cout << "Invalid number of arguments for command '" << cmd <<"' Use 'help' for assistance" << std::endl;
}

void CLIHandler::handleCommand(const std::string& line)
{
    if(line.empty()) return;

    std::string arg;
    std::stringstream ss(line);

    ss >> arg;

    if(auto it = commands.find(arg); it != commands.end())
    {
        std::vector<std::string> args;
        while(ss >> arg)
        {
            args.emplace_back(std::move(arg));
        }
        it->second(std::move(args));
    }
}

void CLIHandler::cmdSet(const std::vector<std::string>& args)
{
    if(args.size() < 2)
    {
        printInvalidArgs("set");
        return;
    }
    keyValueApi.set(args[0], args[1]);
}

void CLIHandler::cmdGet(const std::vector<std::string>& args)
{
    if(args.size() != 1)
    {
        printInvalidArgs("get");
        return;
    }
    keyValueApi.get(args[0]);
}
void CLIHandler::cmdRemove(const std::vector<std::string>& args)
{
    if(args.size() != 1)
    {
        printInvalidArgs("remove");
        return;
    }
    keyValueApi.remove(args[0]);
}

void CLIHandler::cmdShowConfig()
{
    std::cout << "dkv-client: [" << httpClient.getHost() << ":" << httpClient.getPort() <<"] \n"
              << "connectionTimeout : " << httpClient.getConnectionTimeout() << " msec \n"
              << "readTimeout       : " << httpClient.getReadTimeout() << " msec \n"
              << "writeTimeout      : " << httpClient.getWriteTimeout() << " msec \n";
}

void CLIHandler::setTimeout(const std::vector<std::string>& args, const char* func, std::function<void(int)> setter)
{
    if(args.size() != 1)
    {
        printInvalidArgs(func);
        return;
    }
    setter(std::stoi(args[0]));
}

void CLIHandler::cmdHelp()
{
    std::stringstream ss;
    ss << "Distributed Key-Value Storage Client app" << "\n"
       << "Supported arguments:" << "\n"
       << "---- Key-Value API ----" << "\n"
       << "\t set         <key> <value> - add <key, value> to the distributed storage" << "\n"
       << "\t get         <key>         - get value for given <key> from the distributed storage" << "\n"
       << "\t remove      <key>         - remove <key, value> for the given key from the distributed storage" << "\n"
       << "---- Http Client commands ----" << "\n"
       << "\t show-config               - show current http client configuration" << "\n"
       << "\t set-conn-timeout  <value> - set http client's connection timeout (msec)" << "\n"
       << "\t set-read-timeout  <value> - set http client's read timeout (msec)" << "\n"
       << "\t set-write-timeout <value> - set http client's write timeout (msec)" << "\n"
       << "---- Utility commands ----" << "\n"
       << "\t help                      - shows current message" << "\n"
       << "\t exit                      - finish app execution";
    std::cout << ss.str() << std::endl;
}

void CLIHandler::cmdExit()
{
    running = false;
}

void CLIHandler::run()
{
    std::string line;
    running = true;
    while(running)
    {
        std::cout << "dkv-client [" << httpClient.getHost() << ":" << httpClient.getPort() << "] > ";
        if(!std::getline(std::cin, line))
        {
            break;
        }
        handleCommand(line);
    }
}
