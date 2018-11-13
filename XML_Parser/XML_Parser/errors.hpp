#ifndef ERRORS
#define ERRORS
#include <stdexcept>
#include <string>
namespace XML::Error
{
void error(const std::string& er)
{
    throw std::runtime_error(er);
}
}

#endif // ERRORS

