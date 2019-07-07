/**
 * internal_ifxOptEntry.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INTERNAL_IFXOPT_ENTRY_H
#define INTERNAL_IFXOPT_ENTRY_H

#include <string>

#include <ifxOptEntry.h>
#include "ifxDbg.h"

namespace ifx
{

template <typename T>
OptEntry<T>::OptEntry(const std::string  optLong,
                      const char         optShort,
                      const std::string  valName,
                      std::string        helpString,
                      T                 &target,
                      OptionSet          options,
                      Validator<T>      *validator)
                      : OptEntryBase(optLong, optShort, valName, helpString, options), mTarget(target), mValidator(validator)
{}

template <typename T>
OptEntry<T>::~OptEntry()
{
    if (mValidator != nullptr)
    {
        delete mValidator;
    }
}

template <typename T>
int OptEntry<T>::parseValue(const std::string &valStr)
{
    int retVal = IFX_OPT_RESULT_SUCCESS;
    T   value;

    retVal = this->parseValueTypeImpl(valStr, value);

    if (retVal == IFX_OPT_RESULT_SUCCESS)
    {
        // Good extraction, run validation procedure
        if (   this->mValidator == nullptr
            || (*this->mValidator)(value) == true)
        {
            // Validation ok, store the value in target reference
            this->mTarget = value;
            IFX_LOG_DBG("OptEntryInt Successfully extracted value, target=" << this->mTarget);
        }
        else
        {
            retVal = IFX_OPT_ERROR_CUSTOM_VALIDATION_FAILED; // validation error
            IFX_LOG_ERR("OptEntryInt validation error for value: " << valStr);
        }
    }

    return retVal;
}


#define IFX_OPT_INSTANTIATE_TYPE_OPT_ENTRY(type)                                \
    template int OptEntry<type>::parseValue(const std::string &valStr);         \
    template OptEntry<type>::OptEntry(const std::string  optLong,               \
                                      const char         optShort,              \
                                      const std::string  valName,               \
                                      std::string        helpString,            \
                                      type              &target,                \
                                      OptionSet          options   = IFX_OPTION_SET_CLEAR, \
                                      Validator<type>   *validator = nullptr);  \
    template OptEntry<type>::~OptEntry()


} /* namespace ifx */

#endif /* INTERNAL_IFXOPT_ENTRY_H */
