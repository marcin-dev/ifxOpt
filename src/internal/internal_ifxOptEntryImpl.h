/**
 * internal_ifxOptEntry.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INTERNAL_IFXOPT_ENTRY_IMPL_H
#define INTERNAL_IFXOPT_ENTRY_IMPL_H

#include <string>

#include "ifxOptEntry.h"
#include "ifxDbg.h"

namespace ifx
{

template <typename T>
OptEntry<T>::OptEntry(const std::string  optLong,
                      const char         optShort,
                      const std::string  valName,
                      const std::string  helpString,
                      T                 &target,
                      OptionSet          options,
                      Validator        &&validatorFn)
                      : OptEntryBase(optLong, optShort, valName, helpString, options), mTarget(target), mValidatorFn(validatorFn)
{ }

template <typename T>
OptEntry<T>::~OptEntry()
{ }

template <typename T>
int OptEntry<T>::parseValue(const std::string &valStr)
{
    int retVal = IFX_OPT_RESULT_SUCCESS;
    T   value;

    retVal = this->parseValueTypeImpl(valStr, value);

    if (retVal == IFX_OPT_RESULT_SUCCESS)
    {
        // Good extraction, run validation procedure
        if (   false == static_cast<bool>(mValidatorFn) // if there is no function provided
            || true  == mValidatorFn(value))            // or if the validation succeeded
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
                                      const std::string  helpString,            \
                                      type              &target,                \
                                      OptionSet          options     = IFX_OPTION_SET_CLEAR, \
                                      Validator        &&validatorFn = nullptr);  \
    template OptEntry<type>::~OptEntry()


} /* namespace ifx */

#endif /* INTERNAL_IFXOPT_ENTRY_IMPL_H */