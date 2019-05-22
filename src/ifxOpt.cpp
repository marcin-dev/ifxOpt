/**
 * ifxOpt.cpp
 *
 * @date   2019.04
 * @author man
 */

#include "ifxOpt.h"

namespace ifx
{

Opt::Opt()
{
    // TODO Auto-generated constructor stub

}

Opt::~Opt()
{
    // TODO Auto-generated destructor stub
}

template <typename T> void addOptEntry(const std::string  optLong,
                                       const char optShort,
                                       T &target)
{
    // TODO different implementation for basic types
}

int parseOpt(int argc, char* argv[])
{
    // TODO
}

} /* namespace ifx */
