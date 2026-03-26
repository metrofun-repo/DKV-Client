#pragma once

#include <string>

struct BasicError
{ 
    std::string details;
    BasicError() = default;
    BasicError(const std::string& s) : details(s) {}
    BasicError(const char* str) : details(str) {}

    operator const std::string& () const { return details; }
    operator const char * () { return details.c_str(); }
};