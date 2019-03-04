#pragma once

#include <exception>

class NotImplementedException : public std::exception
{
private:
    std::string msg;

public:
    NotImplementedException(const std::string& message = "") : msg(message)
    {
    }

    const char * what() const throw()
    {
        return msg.c_str();
    }
};
