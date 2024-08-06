#include "helpers.hpp"

#include <stdexcept>

std::string getEnvVar(const char *var)
{
    const char *val = getenv(var);
    if (val == NULL)
    {
        throw std::logic_error(std::string(var) + " is not defined");
    }
    return val;
}
