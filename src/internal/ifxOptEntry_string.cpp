/**
 * ifxOptEntry_Int.cpp
 *
 * @date   2019.05
 * @author man
 */

#include <cstdlib>
#include <climits>
#include <string>

#include "internal_ifxOpt.h"
#include "internal_ifxOptEntry.h"
#include "ifxDbg.h"

namespace ifx
{

// ****************************************************************************
// Implementation for Option type: string
// ****************************************************************************

// ****************************************************************************
// Instantiation of Opt class methods and OptEntry class
// ****************************************************************************

IFX_OPT_INSTANTIATE_TYPE_ADD_ENTRY(std::string);
IFX_OPT_INSTANTIATE_TYPE_OPT_ENTRY(std::string);

// ****************************************************************************
// Implementation of OptEntry::parseValue method
// ****************************************************************************

template <>
int OptEntry<std::string>::parseValueTypeImpl(const std::string &valStr, std::string &value)
{
    int retVal = IFX_OPT_RESULT_SUCCESS;

    IFX_LOG_DBG("OptEntry<std::string>::parseOpt, valStr: " << valStr);

    if (valStr.empty() == false)
    {
        // Just copy the string to the target
        value = valStr;
    }
    else
    {
        // Empty input string
        retVal = IFX_OPT_ERROR_VALUE_CANNOT_EXTRACT;
        IFX_LOG_ERR("OptEntry<std::string> error: input string empty");
    }

    return retVal;
}

} /* namespace ifx */
