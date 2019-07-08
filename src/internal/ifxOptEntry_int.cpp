/**
 * ifxOptEntry_Int.cpp
 *
 * @date   2019.05
 * @author man
 */

#include <cstdlib>
#include <climits>

#include "ifxDbg.h"
#include "internal_ifxOptEntryImpl.h"
#include "internal_ifxOptImpl.h"

namespace ifx
{

// ****************************************************************************
// Implementation for Option type: int
// ****************************************************************************

// ****************************************************************************
// Instantiation of Opt class methods and OptEntry class
// ****************************************************************************

IFX_OPT_INSTANTIATE_TYPE_ADD_ENTRY(int);
IFX_OPT_INSTANTIATE_TYPE_OPT_ENTRY(int);

// ****************************************************************************
// Implementation of OptEntry::parseValue method
// ****************************************************************************

template <>
int OptEntry<int>::parseValueTypeImpl(const std::string &valStr, int &value)
{
    // Using C-style procedure to avoid exceptions
    long int  val;
    char     *endptr;
    int       retVal = IFX_OPT_RESULT_SUCCESS;

    IFX_LOG_DBG("OptEntryInt::parseOpt, valStr: " << valStr);

    val = strtol(valStr.c_str(), &endptr, 0);
    if (    endptr != nullptr
        && *endptr == '\0')
    {
        // Good, was able to extract value
        // Check range
        if (   val <= INT_MAX
            && val >= INT_MIN)
        {
            value = static_cast<int>(val);
        }
        else
        {
            retVal = IFX_OPT_ERROR_VALUE_OUT_OF_RANGE; // out of range
            IFX_LOG_ERR("OptEntryInt value out of range");
        }
    }
    else
    {
        retVal = IFX_OPT_ERROR_VALUE_CANNOT_EXTRACT; // cannot convert
        IFX_LOG_ERR("OptEntryInt value conversion error");
    }

    return retVal;
}

} /* namespace ifx */
