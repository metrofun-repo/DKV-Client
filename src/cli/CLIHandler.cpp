#include "CLIHandler.h"

#include <iostream>
#include <sstream>

CLIHandler::CLIHandler()
    : running(false)
{
    commands = 
    {
        { "help",   [&](const std::vector<std::string>&) { cmdHelp(); } },
        { "exit",   [&](const std::vector<std::string>&) { running = false; } }
    };
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

void CLIHandler::cmdHelp()
{
    std::stringstream ss;
    ss << "Distributed Key-Value Storage Client app" << "\n"
       << "Supported arguments:" << "\n"
       << "\t help - shows current message" << "\n"
       << "\t exit - finish app execution";

        
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
        std::cout << "> ";
        if(!std::getline(std::cin, line))
        {
            break;
        }
        handleCommand(line);
    }
}
