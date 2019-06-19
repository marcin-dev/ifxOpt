/**
 * ifxOptEntry.cpp
 *
 * @date   2019.06
 * @author man
 */

#include "ifxOptEntry.h"

#include <iostream>

namespace ifx
{

OptEntryBase::OptEntryBase(const std::string  optLong,
                           const char optShort)
                           : optLong(optLong), optShort(optShort)
{ }

OptEntryBase::~OptEntryBase()
{ }

int OptEntryBase::parseOpt(const std::string &argStr, const char argShort, const std::string &valStr)
{
    std::cout << "parseOpt(argStr=" << argStr << ", argShort=" << argShort << ", valStr=" << valStr << ")" << std::endl;

    int retVal = 1; // by default - not matching string

    std::cout << "optLong: " << this->optLong << ", optShort: " << this->optShort << std::endl;

    if (   this->optLong.compare(argStr) == 0
        || this->optShort == argShort )
    {
        std::cout << "parseOpt MATCH" << std::endl;
        retVal = this->parseOpt(valStr); // run the second virtual method to parse value
    }
    else
    {
        std::cout << "parseOpt NOT MATCH" << std::endl;
    }

    return retVal;
}

} /* namespace ifx */
