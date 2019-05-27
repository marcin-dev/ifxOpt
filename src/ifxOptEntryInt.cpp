/**
 * ifxOptEntryInt.cpp
 *
 * @date   2019.05
 * @author man
 */

#include "ifxOptEntryInt.h"

#include <cstdlib>
#include <climits>

namespace ifx
{

OptEntryInt::OptEntryInt(const std::string  optLong,
                         const char optShort,
                         int &target,
                         Validator<int> &validator) : OptEntry(optLong, optShort), target(target), validator(validator)
{ }

OptEntryInt::~OptEntryInt()
{ }

int OptEntryInt::parseOpt(const std::string &valstr)
{
    // Using C-style procedure to avoid exceptions
    long int  val;
    char     *endptr;
    int       retVal = 0;

    val = strtol(valstr.c_str(), &endptr, 0);
    if (    endptr != nullptr
        && *endptr == '\0')
    {
        // Good, was able to extract value
        // Check range
        if (   val <= INT_MAX
            && val >= INT_MIN)
        {
            // Good range, run validation procedure
            if (this->validator(static_cast<int>(val)) == true)
            {
                // Validation ok, store the value in target reference
                this->target = static_cast<int>(val);
            }
            else
            {
                retVal = -3; // validation error
            }
        }
        else
        {
            retVal = -2; // out of range
        }
    }
    else
    {
        retVal = -1; // cannot convert
    }

    return retVal;
}

} /* namespace ifx */
