#include "cfgchecker.hpp"
namespace awe
{
void CfgChecker::nodeIsOk(const YAML::Node &n)
{
    AString error_str("Node Is Bad, Item: ");
    bool isok = true;
    if(!n["name"].IsDefined())
    {
        isok = false;
        error_str += "<name> ";
    }

    if(!n["tag"].IsDefined())
    {
        isok = false;
        error_str += "<tag> ";
    }

    if(!n["type"].IsDefined())
    {
        isok = false;
        error_str += "<type> ";
    }

    if(!n["label"].IsDefined())
    {
        isok = false;
        error_str += "<label> ";
    }

    if(!isok)
    {
        throw AException(error_str + "not exist!");
    }

}

void CfgChecker::nodeIsDefAndSequence(const YAML::Node &n)
{
    if(n.IsDefined() && n.IsSequence())
    {

    }
    else
    {
        throw AException(n.as<AString>() + " Is Not Defined Or Not Sequence.");
    }
}
} // namespace awe

