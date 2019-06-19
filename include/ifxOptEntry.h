/**
 * ifxOptEntry.h
 *
 * @date   2019.04
 * @author man
 */

#ifndef INCLUDE_IFXOPT_ENTRY_H
#define INCLUDE_IFXOPT_ENTRY_H

#include <string>
#include <iostream>

#include "ifxValidator.h"

namespace ifx
{

class OptEntryBase
{
private:
    const std::string  optLong;
    const char         optShort;

public:
    OptEntryBase(const std::string  optLong,
                 const char optShort);
    virtual ~OptEntryBase();

    int parseOpt(const std::string &argStr, const char argShort, const std::string &valStr);

    virtual int parseOpt(const std::string &valStr) = 0;
};

template <typename T>
class OptEntry : public OptEntryBase
{
protected:
    T                 &target;
    Validator<int>    *validator;

public:
    OptEntry(const std::string  optLong,
             const char optShort,
             T &target,
             Validator<int> *validator = nullptr)
             : OptEntryBase(optLong, optShort), target(target), validator(validator)
    {}

    virtual ~OptEntry()
    {
        if (validator != nullptr)
        {
            delete validator;
        }
    }

    virtual int parseOpt(const std::string &valStr)
    {
        int retVal;
        T   value;

        retVal = this->parseValue(valStr, value);

        if (retVal == 0)
        {
            // Good extraction, run validation procedure
            if (   this->validator == nullptr
                || (*this->validator)(value) == true)
            {
                // Validation ok, store the value in target reference
                this->target = value;
                std::cout << "OptEntryInt Successfully extracted value, target=" << this->target << std::endl;
            }
            else
            {
                retVal = -3; // validation error
                std::cout << "OptEntryInt validation error for value" << std::endl;
            }
        }

        return retVal;
    }

    virtual int parseValue(const std::string &valStr, T &value) = 0;
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_ENTRY_H */
