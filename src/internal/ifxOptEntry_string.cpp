/**
 * ifxOptEntry_Int.cpp
 *
 * @date   2019.05
 * @author man
 */

#include <cstdlib>
#include <climits>
#include <string>
#include <iostream>

#include "internal_ifxOpt.h"
#include "internal_ifxOptEntry.h"

namespace ifx
{

// ****************************************************************************
// Implementation for Option type: string
// ****************************************************************************

// ****************************************************************************
// Instantiation of Opt class methods and OptEntry class
// ****************************************************************************

IFX_OPT_ADD_INSTANTIATE_TYPE(std::string);
IFX_OPT_ENTRY_INSTANTIATE_TYPE(std::string);

// ****************************************************************************
// Implementation of OptEntry::parseValue method
// ****************************************************************************

template <>
int OptEntry<std::string>::parseValue(const std::string &valStr, std::string &value)
{
    int retVal = 0;

    std::cout << "OptEntry<std::string>::parseOpt, valStr: " << valStr << std::endl;

    if (valStr.length() > 0)
    {
        // Just copy the string to the target
        value = valStr;
    }
    else
    {
        // Empty input string
        retVal = -1;
        std::cout << "OptEntry<std::string> error: input string empty" << std::endl;
    }

    return retVal;
}

} /* namespace ifx */
