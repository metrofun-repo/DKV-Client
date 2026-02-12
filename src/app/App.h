#pragma once

#include "cli/CLIHandler.h"

class App
{
    CLIHandler cliHandler;
public:
    App();
    void run();
};