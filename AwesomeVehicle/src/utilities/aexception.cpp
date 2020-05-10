#include "aexception.hpp"


namespace awe
{
AException::AException(const AString &reason) : mWhat(reason)
{

}
AException::~AException()
{

}

} // namespace awe
