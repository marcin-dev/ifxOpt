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
int OptEntry<std::string>::parseValueTypeImpl(const std::string &valStr, std::string &value)
{
    int retVal = IFX_OPT_RESULT_SUCCESS;

    std::cout << "OptEntry<std::string>::parseOpt, valStr: " << valStr << std::endl;

    if (valStr.empty() == false)
    {
        // Just copy the string to the target
        value = valStr;
    }
    else
    {
        // Empty input string
        retVal = IFX_OPT_ERROR_VALUE_CANNOT_EXTRACT;
        std::cout << "OptEntry<std::string> error: input string empty" << std::endl;
    }

    return retVal;
}

} /* namespace ifx */
