#ifndef ERRORS
#define ERRORS
#include <stdexcept>
namespace XML::Error
{
void error(const string& er)
{
    throw std::runtime_error(er);
}
}

#endif // ERRORS

