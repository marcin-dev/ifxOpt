/**
 * ifxOptEntryInt.cpp
 *
 * @date   2019.05
 * @author man
 */

#include "ifxOptEntryInt.h"

#include <cstdlib>
#include <climits>
#include <iostream>

namespace ifx
{

DefaultValidator<int>  OptEntryInt::defaultValidator;

OptEntryInt::OptEntryInt(const std::string  optLong,
                         const char optShort,
                         int &target,
                         Validator<int> &validator) : OptEntry(optLong, optShort), target(target), validator(validator)
{ }

OptEntryInt::~OptEntryInt()
{ }

int OptEntryInt::parseOpt(const std::string &valStr)
{
    // Using C-style procedure to avoid exceptions
    long int  val;
    char     *endptr;
    int       retVal = 0;

    std::cout << "OptEntryInt::parseOpt, valStr: " << valStr << std::endl;

    val = strtol(valStr.c_str(), &endptr, 0);
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
                std::cout << "OptEntryInt Successfully extracted value, target=" << this->target << std::endl;
            }
            else
            {
                retVal = -3; // validation error
                std::cout << "OptEntryInt validation error for value" << std::endl;
            }
        }
        else
        {
            retVal = -2; // out of range
            std::cout << "OptEntryInt value out of range" << std::endl;
        }
    }
    else
    {
        retVal = -1; // cannot convert
        std::cout << "OptEntryInt value conversion error" << std::endl;
    }

    return retVal;
}

} /* namespace ifx */
