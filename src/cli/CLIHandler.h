#pragma once

#include <vector>
#include <string>
#include <functional>
#include <unordered_map>

class CLIHandler
{
    using CommandKey = std::string;
    using CommandHandler = std::function<void(const std::vector<std::string>&)>;
    bool running;
    std::unordered_map<CommandKey, CommandHandler> commands;

    void handleCommand(const std::string& line);
    void cmdHelp();
    void cmdExit();
public:
    CLIHandler();
    void run();
};