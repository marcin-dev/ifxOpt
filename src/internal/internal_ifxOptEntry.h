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
                      const char         optShort,
                      const std::string  valName,
                      std::string        helpString,
                      T                 &target,
                      bool               mandatory,
                      bool               valMandatory,
                      Validator<T>      *validator)
                      : OptEntryBase(optLong, optShort, valName, helpString, mandatory, valMandatory), target(target), validator(validator)
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

    if (retVal == IFX_OPT_RESULT_SUCCESS)
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
            retVal = IFX_OPT_ERROR_CUSTOM_VALIDATION_FAILED; // validation error
            std::cout << "OptEntryInt validation error for value" << std::endl;
        }
    }

    return retVal;
}


#define IFX_OPT_ENTRY_INSTANTIATE_TYPE(type)                                    \
    template int OptEntry<type>::parseOpt(const std::string &valStr);           \
    template OptEntry<type>::OptEntry(const std::string  optLong,               \
                                      const char         optShort,              \
                                      const std::string  valName,               \
                                      std::string        helpString,            \
                                      type              &target,                \
                                      bool               mandatory = false,     \
                                      bool               valMandatory = false,  \
                                      Validator<type>   *validator = nullptr);  \
    template OptEntry<type>::~OptEntry()


} /* namespace ifx */

#endif /* INTERNAL_IFXOPT_ENTRY_H */
