#pragma once

#include <vector>
#include <string>
#include <functional>
#include <unordered_map>

class KeyValueApi;
class HttpClient;

class CLIHandler
{
    using CommandKey = std::string;
    using CommandHandler = std::function<void(const std::vector<std::string>&)>;

    bool running;
    HttpClient& httpClient;
    KeyValueApi& keyValueApi;
    std::unordered_map<CommandKey, CommandHandler> commands;

    void printInvalidArgs(const char* cmd) const;

    void handleCommand(const std::string& line);

    void cmdSet(const std::vector<std::string>& args);
    void cmdGet(const std::vector<std::string>& args);
    void cmdRemove(const std::vector<std::string>& args);
    
    void cmdShowConfig();
    void setTimeout(const std::vector<std::string>& args, const char* func, std::function<void(int)> setter);

    void cmdHelp();
    void cmdExit();
public:
    CLIHandler(HttpClient& client, KeyValueApi& api);
    void run();
};