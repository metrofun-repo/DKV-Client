#include "app/App.h"
#include <iostream>

AppConfig parseArgs(int argc, char* argv[])
{
    AppConfig cfg;

    auto readInteger = [&](const std::string& arg, int& index, int& target)
    {
        if(index + 1 >= argc)
        {
            std::cout << "Missing value for argument: " << arg << std::endl;
            return false;
        }
        try
        {
            target = std::stoi(argv[++index]);
        }
        catch(...)
        {
            std::cout << "Invalid numeric value for argument: " << arg << std::endl;
            return false;
        }
        return true;
    };

    for(int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if(arg == "--host")
        {
            if(i + 1 >= argc)
            {
                std::cout << "Missing value for argument: " << arg << std::endl;
                break;
            }
            cfg.host = argv[++i];
        }
        else if(arg == "--port")
        {
            readInteger(arg, i, cfg.port);
        }
        else if(arg == "--connectionTimeout")
        {
            readInteger(arg, i, cfg.connectionTimeoutMs);
        }
        else if(arg == "--readTimeout")
        {
            readInteger(arg, i, cfg.readTimeoutMs);
        }
        else if(arg == "--writeTimeout" && i + 1 < argc)
        {
            readInteger(arg, i, cfg.writeTimeoutMs);
        }
        else
        {
            std::cout << "Unknown argument: " << arg << std::endl;
        }
    }
    return cfg;
}

int main(int argc, char* argv[])
{
    App app(parseArgs(argc, argv));

    app.run();
    
    return 0;
}