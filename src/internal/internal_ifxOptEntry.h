/**
 * internal_ifxOptEntry.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INTERNAL_IFXOPT_ENTRY_H
#define INTERNAL_IFXOPT_ENTRY_H

#include <string>
#include <iostream>

#include <ifxOptEntry.h>

namespace ifx
{

template <typename T>
OptEntry<T>::OptEntry(const std::string  optLong,
                      const char optShort,
                      T &target,
                      Validator<T> *validator)
                      : OptEntryBase(optLong, optShort), target(target), validator(validator)
{}

template <typename T>
OptEntry<T>::~OptEntry()
{
    if (validator != nullptr)
    {
        delete validator;
    }
}

template <typename T>
int OptEntry<T>::parseOpt(const std::string &valStr)
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


#define IFX_OPT_ENTRY_INSTANTIATE_TYPE(type)                                \
    template int OptEntry<type>::parseOpt(const std::string &valStr);       \
    template OptEntry<type>::OptEntry(const std::string  optLong,           \
                                      const char optShort,                  \
                                      type &target,                         \
                                      Validator<type> *validator = nullptr);\
    template OptEntry<type>::~OptEntry()


} /* namespace ifx */

#endif /* INTERNAL_IFXOPT_ENTRY_H */
